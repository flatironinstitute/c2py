#pragma once
#include <fstream>
#include "cpp_name.hpp"
#include "py_converter.hpp"
#include "converters/basic_types.hpp"
namespace c2py {

  // FIXME: move to top ?
  using namespace std::string_literals;

  /// Basic C++ interface for a Python dict
  /// It handles the [] operator with convertion for expressions of
  /// the kind  d["a"] = x; // where x in C++ -> converted to Python
  struct pydict : pyref {
    /// New empty dict
    pydict() : pyref{PyDict_New()} {}

    /// From a borrowed ref ob
    pydict(PyObject *ob) : pyref{pyref::borrowed(ob)} { assert(PyDict_Check(ob)); }

    ///
    pydict(pyref p) : pyref{p} {}

    struct proxy { // helper struct for the [] operator
      PyObject *self;
      const char *key;
      proxy &operator=(auto &x) {
        PyDict_SetItemString(self, key, c2py::pyref{c2py::cxx2py(x)});
        // NB : PyDict_SetItemString does NOT steal the reference (cf Python API),
        // so we put the new reference made by cxx2py
        // in a pyref which will release it at destruction.
        return *this;
      }
      operator PyObject *() const { return PyDict_GetItemString(self, key); } // NB : borrowed ref
    };

    /// d["a"] = x;
    proxy operator[](const char *key) { return proxy{*this, key}; }

    /// d["a"] is a PyObject *
    proxy const operator[](const char *key) const { return proxy{*this, key}; }

    /// Contains
    bool contains(const char *key) const { return PyDict_GetItemString(*this, key) != nullptr; }

    /// List of the keys (same order as the Python dict)
    [[nodiscard]] std::vector<std::string> keys() const {
      std::vector<std::string> result;
      pyref keys         = PyDict_Keys(*this);               // new ref
      PyListObject *list = (PyListObject *)(PyObject *)keys; //NOLINT
      int l              = PySequence_Fast_GET_SIZE(list);
      for (int i = 0; i < l; ++i) {
        PyObject *k = PySequence_Fast_GET_ITEM(list, i); // borrowed
        result.emplace_back(PyUnicode_AsUTF8(k));
      }
      return result;
    }
  };

  // --------------------

  /// Extract elements from a pydict, converting to C++.
  /// It keeps memory of the keys already called
  /// and report a list of various errors at the end:
  /// - keys that were not presents
  /// - impossible convertions to C++.
  /// This is mainly use in building a synthetic constructor of a struct from a Python dict.
  class pydict_extractor {

    pydict dic;
    std::stringstream err;
    std::vector<std::string> used_keys;

    public:
    pydict_extractor(PyObject *kw) : dic((kw ? c2py::pyref::borrowed(kw) : c2py::pyref{PyDict_New()})) {}

    private:
    std::string make_error_mandatory(PyObject *obj, const char *var_name, std::string const &var_cpp_type_name) {
      std::stringstream out;
      out << "\n The parameter " << var_name << " does not have the right type : expecting " << var_cpp_type_name << " in C++, but got '"
          << Py_TYPE(obj)->tp_name << "' in Python.";
      return out.str();
    }

    template <typename T> void call_impl(const char *varname, T &x, PyObject *pyarg) {
      used_keys.emplace_back(varname);
      if (py_converter<T>::is_convertible(pyarg, false))
        x = py2cxx<T>(pyarg);
      else {
        err << make_error_mandatory(pyarg, varname, cpp_name<T>);
        py_converter<T>::is_convertible(pyarg, true); // raise exception
        if (PyErr_Occurred()) { err << "   Explanation: " << get_python_error() << "\n"; }
      }
    }

    public:
    void operator()(const char *varname, auto &x, bool has_default = false) {
      PyObject *pyarg = dic[varname];
      if (pyarg)
        call_impl(varname, x, pyarg);
      else if (not has_default)
        err << "\n Mandatory parameter '" << varname << "' is missing. \n";
    }

    // get the object of name `name` from the dict and convert into a T.
    // if the dict has no object name, throws.
    template <typename T> T get(const char *name) {
      PyObject *pyarg = dic[name];
      if (not pyarg) throw std::runtime_error("The mandatory parameter '"s + name + "' is missing");
      used_keys.emplace_back(name);
      if (not py_converter<T>::is_convertible(pyarg, true)) throw std::runtime_error(make_error_mandatory(pyarg, name, cpp_name<T>));
      return py2cxx<T>(pyarg);
    }

    private:
    /// A detailed report of all the errors.
    /// report_unused_keys: if true and some keys of the dict have not been called for
    /// by either () or get, we report them.
    void report_unused_keys() {
      auto all_keys = dic.keys();
      std::sort(all_keys.begin(), all_keys.end());
      std::sort(used_keys.begin(), used_keys.end());
      std::vector<std::string> diff;
      std::set_difference(all_keys.begin(), all_keys.end(), used_keys.begin(), used_keys.end(), std::inserter(diff, diff.begin()));
      for (auto const &k : diff) err << "\n The parameter '" << k << "' was not used.";
    }

    public:
    /// Return 0 if no errors, and -1 if some errors has occurred
    /// If errors, it also set the Python exception with a complete report
    int check() {
      report_unused_keys();
      auto s     = err.str();
      bool error = not s.empty();
      if (error) PyErr_SetString(PyExc_RuntimeError, s.c_str());
      return (error ? -1 : 0);
    }
  };

} // namespace c2py

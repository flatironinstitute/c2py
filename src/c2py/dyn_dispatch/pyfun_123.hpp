#pragma once
#include <vector>
#include <functional>
#include <memory>
#include <algorithm>
#include "../pytypes/wrap.hpp"

namespace c2py {

  template <typename R, typename... T> std::string simple_signature_123() { return (cpp_qname<T>() + ... + "") + " -> " + cpp_qname<R>(); }

  // -------------------  pyfun_123 --------------------

  class pyfun_123 {
    [[maybe_unused]] std::string (*sig)();
    std::vector<int> converter_indices; // Indices into the static convert_checker vector
    virtual PyObject *call(PyObject *x, PyObject *y, PyObject *z) const = 0;

    protected:
    pyfun_123(std::vector<int> &&indices, std::string (*sig)()) : sig{sig}, converter_indices(std::move(indices)) {}

    public:
    virtual ~pyfun_123() = default;

    [[nodiscard]] std::string signature() const { return (*sig)(); }

    [[nodiscard]] std::vector<int> const &get_converter_indices() const { return converter_indices; }

    PyObject *operator()(PyObject *x, PyObject *y, PyObject *z) const {
      try {
        return call(x, y, z);
      } catch (std::exception const &e) {
        auto err = std::string(".. Error  : \n") + e.what();
        PyErr_SetString(PyExc_RuntimeError, err.c_str());
      }
      return nullptr;
    }
  };

  // ------------

  template <typename R, typename... T> class pyfun_123_impl : public pyfun_123 {
    using fnt_ptr_t = R (*)(T...);
    fnt_ptr_t f;

    public:
    pyfun_123_impl(fnt_ptr_t f, std::vector<int> &&indices) : pyfun_123{std::move(indices), &simple_signature_123<R, T...>}, f{f} {}

    PyObject *call(PyObject *x, PyObject *y, PyObject *z) const override {
      auto args = std::tie(x, y, z);
      auto call_helper = [this, &args]<size_t... Is>(std::index_sequence<Is...>) {
        if constexpr (std::is_same_v<void, R>) {
          f(py2cxx<T>(std::get<Is>(args))...);
          Py_RETURN_NONE;
        } else {
          return cxx2py(f(py2cxx<T>(std::get<Is>(args))...));
        }
      };
      return call_helper(std::make_index_sequence<sizeof...(T)>{});
    }
  };

  // ------------  dispatcher_123 --------------------

  class dispatcher_123 {
    public:
    // Static vector of converter checkers: PyObject* -> bool
    static std::vector<std::function<bool(PyObject *, bool)>> convert_checker;

    private:
    std::vector<std::unique_ptr<pyfun_123>> ov_list;

    public:
    template <typename... U> dispatcher_123(U &&...u) { ((void)ov_list.push_back(std::forward<U>(u)), ...); }

    // Call operator: checks convertibility and dispatches to the first matching overload
    PyObject *operator()(PyObject *x, PyObject *y = nullptr, PyObject *z = nullptr) const {
      // Iterate through overloads and check convertibility
      for (auto const &ov : ov_list) {
        auto const &indices = ov->get_converter_indices();
        bool convertible    = true;

        // Check first argument (always present)
        if (indices.size() > 0 && !convert_checker[indices[0]](x, false)) {
          convertible = false;
          continue;
        }

        // Check second argument if present
        if (indices.size() > 1 && y != nullptr) {
          if (!convert_checker[indices[1]](y, false)) {
            convertible = false;
            continue;
          }
        }

        // Check third argument if present
        if (indices.size() > 2 && z != nullptr) {
          if (!convert_checker[indices[2]](z, false)) {
            convertible = false;
            continue;
          }
        }

        // Found a match, call it
        if (convertible) { return (*ov)(x, y, z); }
      }

      // No match found, build error message
      std::stringstream err;
      err << "[c2py] Can not call the function with the arguments\n";
      if (x) err << "   " << PyUnicode_AsUTF8(pyref{PyObject_Str(x)}) << "\n";
      if (y) err << "   " << PyUnicode_AsUTF8(pyref{PyObject_Str(y)}) << "\n";
      if (z) err << "   " << PyUnicode_AsUTF8(pyref{PyObject_Str(z)}) << "\n";
      err << "The dispatch to C++ failed with the following error(s):\n";

      int c = 0;
      for (auto const &ov : ov_list) {
        ++c;
        auto const &indices = ov->get_converter_indices();
        err << "[" << c << "] " << ov->signature() << "\n";

        // Try to get detailed error for each argument
        if (indices.size() > 0) {
          convert_checker[indices[0]](x, true);
          err << "    -- Arg 0: " << c2py::get_python_error() << "\n";
        }
        if (indices.size() > 1 && y != nullptr) {
          convert_checker[indices[1]](y, true);
          err << "    -- Arg 1: " << c2py::get_python_error() << "\n";
        }
        if (indices.size() > 2 && z != nullptr) {
          convert_checker[indices[2]](z, true);
          err << "    -- Arg 2: " << c2py::get_python_error() << "\n";
        }
        err << "\n";
      }

      PyErr_SetString(PyExc_TypeError, err.str().c_str());
      return nullptr;
    }

    [[nodiscard]] std::string signatures() const {
      std::stringstream fs;
      for (auto const &ov : ov_list) fs << ov->signature() << "\n";
      return fs.str();
    }
  };


  // Helper function to create pyfun_123 objects
  template <typename R, typename... T> std::unique_ptr<pyfun_123> cfun_123(R (*f)(T...), std::vector<int> indices) {
    return std::make_unique<pyfun_123_impl<R, T...>>(f, std::move(indices));
  }

  // Helper to register a converter and return its index
  template <typename T> int register_converter() {
    auto checker = [](PyObject *obj, bool raise_exception) -> bool { return py_converter<std::decay_t<T>>::is_convertible(obj, raise_exception); };
    dispatcher_123::convert_checker.push_back(checker);
    return dispatcher_123::convert_checker.size() - 1;
  }

} // namespace c2py

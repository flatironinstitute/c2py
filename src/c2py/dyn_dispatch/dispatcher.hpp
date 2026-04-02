#pragma once
#include <algorithm>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include "pycfun_kw.hpp"
#include "binaryfunc.hpp"
namespace c2py {

  // =============== dynamic dispatcher ========================

  // Gather a set of overload and handle the calls and error reporting
  template <typename Eraser, bool Constructors = false> struct dispatcher_t {
    std::vector<std::unique_ptr<Eraser>> ov_list;
    std::unique_ptr<std::map<std::string, std::string>> deprecated_params; // old_name -> new_name, null when unused

    template <typename... U> dispatcher_t(U &&...u) { ((void)ov_list.push_back(std::forward<U>(u)), ...); }

    // Builder: attach a deprecated parameter rename map
    dispatcher_t &&with_deprecated_params(std::map<std::string, std::string> m) && {
      deprecated_params = std::make_unique<std::map<std::string, std::string>>(std::move(m));
      return std::move(*this);
    }

    private:
    PyObject *call_impl(PyObject *self, PyObject *args, PyObject *kwargs) const;

    public:
    // Call each overload. The first available is used.
    // if not is ok, we recall the is_callable to build a proper error with the exceptions
    auto operator()(PyObject *self, PyObject *args, PyObject *kwargs = nullptr) const {
      PyObject *r = call_impl(self, args, kwargs);
      if constexpr (not Constructors)
        return r;
      else
        return int(r == nullptr ? -1 : 0);
    }

    //
    [[nodiscard]] std::string signatures() const {
      std::stringstream fs;
      for (auto const &ov : ov_list) fs << ov->signature() << "\n";
      return fs.str();
    }

    // overload doc (string) in case only one overload ...
    // FIXME : to make generated code simpler in most cases.
    [[nodiscard]] std::string doc(const char *doc_string, std::vector<std::vector<std::string>> const &param_types = {},
                                  std::vector<std::string> const &return_types = {}) const;
  };

  // ==============================

  using dispatcher_f_kw_t = dispatcher_t<pycfun_kw, false>;
  using dispatcher_c_kw_t = dispatcher_t<pycfun_kw, true>;

  // Transform a method pointer M into a `getter` type
  // of Python, cf https://docs.python.org/3/c-api/structures.html
  //
  template <auto M> static PyObject *getter_from_method(PyObject *self, void *) {
    static c2py::dispatcher_f_kw_t ovs = {c2py::cfun(M)};
    return ovs(self, nullptr, nullptr);
  }

  // Same as getter_from_method, but for inherited methods where M has base class type.
  // Cls is the derived class that we are wrapping.
  template <typename Cls, auto M> static PyObject *getter_from_method_B(PyObject *self, void *) {
    static c2py::dispatcher_f_kw_t ovs = {c2py::cfun_B<Cls>(M)};
    return ovs(self, nullptr, nullptr);
  }

  // Getter from a free function whose first argument is self
  template <auto F> static PyObject *getter_from_fun(PyObject *self, void *) {
    static c2py::dispatcher_f_kw_t ovs = {c2py::cmethod(F, "self")};
    return ovs(self, nullptr, nullptr);
  }

  // Same as setter_from_method, but for inherited methods where F has base class type.
  // Cls is the derived class that we are wrapping.
  template <typename Cls, auto F> static int setter_from_method_B(PyObject *self, PyObject *value, void *closure) {
    if (value == nullptr) return (PyErr_SetString(PyExc_AttributeError, static_cast<const char *>(closure)), -1);
    static c2py::dispatcher_f_kw_t d = {c2py::cfun_B<Cls>(F, "i")};
    d(self, c2py::pyref(PyTuple_Pack(1, value)), nullptr);
    return 0;
  }

  // Setter from a method pointer.
  // closure must point to the attribute-name C-string used in the "cannot delete" error.
  template <auto F> static int setter_from_method(PyObject *self, PyObject *value, void *closure) {
    if (value == nullptr) return (PyErr_SetString(PyExc_AttributeError, static_cast<const char *>(closure)), -1);
    static c2py::dispatcher_f_kw_t d = {c2py::cfun(F, "i")};
    d(self, c2py::pyref(PyTuple_Pack(1, value)), nullptr);
    return 0;
  }

  // Setter from a free function whose first argument is self.
  // closure must point to the attribute-name C-string used in the "cannot delete" error.
  template <auto F> static int setter_from_fun(PyObject *self, PyObject *value, void *closure) {
    if (value == nullptr) return (PyErr_SetString(PyExc_AttributeError, static_cast<const char *>(closure)), -1);
    static c2py::dispatcher_f_kw_t d = {c2py::cmethod(F, "self", "i")};
    d(self, c2py::pyref(PyTuple_Pack(1, value)), nullptr);
    return 0;
  }

  // Given a string containing placeholders {tag_i} for i=0..N-1, replace {tag_i} by the string vec[i].
  std::string replace_tags(std::string str, std::string const &tag, std::vector<std::string> const &vec);

} // namespace c2py

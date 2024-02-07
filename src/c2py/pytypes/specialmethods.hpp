#pragma once
#include "../util/macros.hpp"
#include "../py_converter.hpp"
#include "../converters/basic_types.hpp"
namespace c2py {

  // -------------------- Members ----------------------------

  namespace details {

    // Need Cls and Cls2 for the case when M is a pointer of a PARENT class,
    //
    template <typename Cls, typename T, typename Cls2> static PyObject *get_member_impl(PyObject *self, void *, T Cls2::*M) {
      static_assert(std::is_base_of_v<Cls2, Cls>);
      auto &self_c = py_converter<Cls>::py2c(self);
      try {
        return py_converter<std::decay_t<T>>::c2py(self_c.*M);
      } catch (std::exception const &e) {
        auto err = std::string(".. Error in getting the attribute [converter C++ -> Py failed] : \n.. ") + e.what();
        PyErr_SetString(PyExc_RuntimeError, err.c_str());
        return nullptr;
      }
    }

    template <typename Cls, typename T, typename Cls2> static int set_member_impl(PyObject *self, PyObject *value, void *, T Cls2::*M) {
      static_assert(std::is_base_of_v<Cls2, Cls>);
      if (value == nullptr) {
        PyErr_SetString(PyExc_TypeError, "Cannot delete the attribute");
        return -1;
      }
      if (!py_converter<T>::is_convertible(value, true)) return -1; // exception is set by the converter
      auto &self_c = py_converter<Cls>::py2c(self);
      try {
        self_c.*M = py_converter<T>::py2c(value);
      } catch (std::exception const &e) {
        auto err = std::string(".. Error in setting the attribute : \n.. ") + e.what();
        PyErr_SetString(PyExc_RuntimeError, err.c_str());
        return -1;
      }
      return 0;
    }
    template <typename Cls, typename T> constexpr Cls _detect_cls(T Cls::*M);
    template <auto M> using cls_from_method_ptr = decltype(_detect_cls(M));

  } // namespace details

  // Makes a `getter` Python function from the member pointer M
  // NB impl: I do not use an inline lambda but rather get_member_impl since it takes M as an argument,
  // so it avoids to instantiate it for each M for a given class Cls and type T.
  template <auto M, typename Cls> static PyObject *get_member(PyObject *self, void *p) { return details::get_member_impl<Cls>(self, p, M); }

  template <auto M, typename Cls> static int set_member(PyObject *self, PyObject *value, void *p) {
    return details::set_member_impl<Cls>(self, value, p, M);
  }

  // From a member point M of some class Cls (detected), return the PyGetSetDef structure.
  template <auto M, typename Cls = details::cls_from_method_ptr<M>>
  static constexpr PyGetSetDef getsetdef_from_member(const char *name, const char *doc) {
    return {name, c2py::get_member<M, Cls>, c2py::set_member<M, Cls>, doc, nullptr};
  }

  // -------------------- [] ----------------------------

  template <typename T, typename A> static decltype(auto) getitem(T const &a, A i) { return a[i]; }

  template <typename T, typename A1> static void setitem(T &a, A1 i, std::decay_t<decltype(a[i])> const &val) { a[i] = val; }

  template <typename T> static Py_ssize_t tpxx_size(PyObject *self) { return py2cxx<T>(self).size(); }

  // -------------------- tp_richcompare ----------------------------

  // FIXME: ok, but it would not handle more complex comparison with other types...
  // To refine ?
  template <typename Cls> static PyObject *tp_richcompare(PyObject *a, PyObject *b, int op) {

// NOLINTNEXTLINE
#define CLAIR_C2PY_COMPARE_IMPL(OP)                                                                                                                  \
  if constexpr (requires(Cls const &x, Cls const &y) { x OP y; }) {                                                                                  \
    return py_converter<bool>::c2py(py_converter<Cls>::py2c(a) OP py_converter<Cls>::py2c(b));                                                       \
  } else {                                                                                                                                           \
    PyErr_SetString(PyExc_NotImplementedError, "Comparison operator " CLAIR_AS_STRING(OP) " not implemented");                                       \
    return NULL;                                                                                                                                     \
  }

    // Put string once and for all for all type
    switch (op) {
      case Py_EQ: CLAIR_C2PY_COMPARE_IMPL(==)
      case Py_NE: CLAIR_C2PY_COMPARE_IMPL(!=)
      case Py_LT: CLAIR_C2PY_COMPARE_IMPL(<)
      case Py_GT: CLAIR_C2PY_COMPARE_IMPL(>)
      case Py_LE: CLAIR_C2PY_COMPARE_IMPL(<=)
      case Py_GE: CLAIR_C2PY_COMPARE_IMPL(>=)
      default: break;
    }
    return nullptr;
  }

#undef CLAIR_C2PY_COMPARE_IMPL

} // namespace c2py

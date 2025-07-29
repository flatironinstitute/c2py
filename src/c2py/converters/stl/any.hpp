#pragma once
#include <any>
#include <cmath>
#include "./common.hpp"

namespace c2py {

  template <> struct py_converter<std::any> {

    static constexpr const char *tp_name = "capsule";

    static void capsule_destructor(PyObject *capsule) {
      void *p = PyCapsule_GetPointer(capsule, "std::any");
      assert(p);
      auto *a_ptr = static_cast<std::any *>(p);
      delete a_ptr; //NOLINT
    }

    template <typename U> static PyObject *c2py(U &&u) {
      auto *p = new std::any{std::forward<U>(u)}; //NOLINT
      return PyCapsule_New(p, "std::any", capsule_destructor);
    }

    // --------------------------------------

    static bool is_convertible(PyObject *ob, bool raise_exception) {
      bool ok = (PyCapsule_CheckExact(ob) and (std::string_view{PyCapsule_GetName(ob)} == "std::any"));
      if (!ok and raise_exception) { PyErr_SetString(PyExc_TypeError, ("Cannot convert "s + to_string(ob) + " to std::any"s).c_str()); }
      return ok;
    }

    // --------------------------------------

    static std::any &py2c(PyObject *ob) {
      void *p = PyCapsule_GetPointer(ob, "std::any");
      assert(p);
      return *static_cast<std::any *>(p);
    }
  };

  // -------------------------------------------------------

  template <typename T> struct py_converter_as_any : py_converter<std::any> {

    using base_t = py_converter<std::any>;

    static bool is_convertible(PyObject *ob, bool raise_exception) {
      if (!base_t::is_convertible(ob, raise_exception)) return false;
      return base_t::py2c(ob).type() == typeid(T);
    }

    static T &py2c(PyObject *ob) { return std::any_cast<T &>(base_t::py2c(ob)); }
  };
} // namespace c2py
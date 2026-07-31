#pragma once
#include "../py_converter.hpp"
#include "../pytypes/wrap.hpp"
#include <type_traits>

// Two global tables of PyTypeObject, stored at the top of the interpreter so that each module can
// retrieve the PyTypeObject of the types wrapped by the other modules :
//
//   __main__.__c2py_table    the types wrapped by the c2py modules. Written by c2py only.
//   __main__.__cpp2py_table  the table of the legacy cpp2py, written by the legacy modules.
//
// A lookup goes through the c2py table first. A type found only in the cpp2py table is wrapped by a
// module built with the legacy cpp2py, whose holder is { PyObject_HEAD; T *_c; } : it has no parent
// and no is_const field, so the converters can not treat it as a wrap<T>.
namespace c2py {

  // Table : c++ type name -> PyTypeObject *
  using pto_table_t = std::map<std::string, PyTypeObject *>;

  // Get the c2py PyTypeObject table, initialize it if necessary
  std::shared_ptr<pto_table_t> get_pto_table();

  // Each translation holds a shared pointer to the c2py PyTypeObject table
  static std::shared_ptr<pto_table_t> conv_table_sptr = get_pto_table(); //NOLINT

  // The result of the lookup of a C++ type in the tables.
  struct pto_lookup_t {
    PyTypeObject *pto = nullptr; // null if the type is wrapped nowhere. A Python exception is then set.
    bool legacy       = false;   // pto comes from the legacy cpp2py table : holder without parent and is_const
  };

  // Look up ind in the c2py table, then in the legacy cpp2py table.
  pto_lookup_t lookup_pto_in_tables(std::type_index const &ind);

  // Register pto in the c2py table, under the mangled name of the C++ type it wraps.
  void register_pto_in_table(const char *mangled_name, PyTypeObject *pto);

  // Expose the PyTypeObject of T in the module namespace under pyname, and register it.
  // Returns false, with a Python exception set, if the module can not be initialized : the generated
  // init then returns NULL, i.e. the import fails with that exception.
  //
  // noexcept : this is called from PyInit, which is extern "C" and which CPython calls from C, so an
  // exception crossing that frame terminates the process instead of failing the import. The table
  // plumbing does throw, hence the function-try-block. Its handlers must not throw either, which is
  // why they report through PyErr_Format rather than build a std::string.
  template <typename T> [[nodiscard]] bool add_type_object_to_main(const char *pyname, PyObject *_main_) noexcept try {
    // tp_doc<T> is a global const std::string with static storage duration; .data() is valid
    // for the lifetime of the shared library (Python finalization precedes dlclose).
    c2py::wrap_pytype<T>.tp_doc = c2py::tp_doc<T>.data();
    Py_INCREF(&c2py::wrap_pytype<T>);
    // PyModule_AddObject steals the reference on success; release the INCREF on failure.
    if (PyModule_AddObject(_main_, pyname, (PyObject *)&c2py::wrap_pytype<T>) < 0) {
      Py_DECREF(&c2py::wrap_pytype<T>);
      return false;
    }
    register_pto_in_table(std::type_index(typeid(T)).name(), &c2py::wrap_pytype<T>);
    return true;
  } catch (std::exception const &e) {
    PyErr_Format(PyExc_ImportError, "c2py: can not register '%s' : %s", pyname, e.what());
    return false;
  } catch (...) {
    PyErr_Format(PyExc_ImportError, "c2py: can not register '%s' : unknown C++ exception", pyname);
    return false;
  }

  //---------------------  wrapped type -----------------------------

  template <typename T>
    requires(is_wrapped<T> and not std::is_enum_v<T>)
  struct py_converter<T> {

    static_assert(not std::is_reference_v<T>); // The T = U& case is a separate specialization

    template <typename U> static PyObject *c2py(U &&x) {
      PyTypeObject *p = lookup_pto_in_tables(typeid(T)).pto;
      if (p == nullptr) return nullptr;
      auto *self = (wrap<T> *)p->tp_alloc(p, 0);
      if (self != NULL) { self->_c = new T{std::forward<U>(x)}; } // NOLINT
      return (PyObject *)self;
    }

    static T &py2c(PyObject *ob) {
      auto *_c = ((wrap<T> *)ob)->_c;
      if (_c == NULL) {
        std::cerr << "Severe internal error : _c is null in py2c\n";
        std::terminate();
      }
      return *_c;
    }

    static bool is_const(PyObject *ob) { return ((wrap<T> *)ob)->is_const; } // specific to this converter

    static bool is_convertible(PyObject *ob, bool raise_exception) {
      PyTypeObject *p = lookup_pto_in_tables(typeid(T)).pto;
      if (p == nullptr) return false;
      if (PyObject_TypeCheck(ob, p)) {
        if (((wrap<T> *)ob)->_c != NULL) return true;
        auto err = std::string{"Severe internal error : Python object of "} + p->tp_name + " has a _c NULL pointer !!";
        if (raise_exception) PyErr_SetString(PyExc_TypeError, err.c_str());
        return false;
      }
      auto err = std::string{"Python object is not a "} + p->tp_name + " but a " + Py_TYPE(ob)->tp_name;
      if (raise_exception) PyErr_SetString(PyExc_TypeError, err.c_str());
      return false;
    }
  };

  // ------------------------------------

  template <typename T>
    requires(is_wrapped<std::remove_const_t<T>>)
  struct py_converter<T &> {
    // this converter is only used C-> Py. For Py-> C, the pycfun_kw takes care of the reference.
    // FIXME : it should not. The previous converter should return T, and we should use this one in pycfun_kw.
    static bool is_convertible(PyObject *ob, bool raise_exception) = delete;
    static T &py2c(PyObject *ob)                                   = delete;

    //
    static PyObject *c2py(T &x, PyObject *guardian) {
      PyTypeObject *p = lookup_pto_in_tables(typeid(T)).pto;
      if (p == nullptr) return nullptr;
      auto *self = (wrap<T> *)p->tp_alloc(p, 0);
      if (self != NULL) {
        self->_c       = &x;
        self->parent   = guardian;
        self->is_const = std::is_const_v<T>;
        Py_XINCREF(guardian); // parent owns a reference
      }
      return (PyObject *)self;
    }
    // p2yc and is_convertible are never used.
  };

} // namespace c2py

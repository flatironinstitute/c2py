#pragma once
#include "../py_converter.hpp"
#include "../pytypes/wrap.hpp"
#include <type_traits>

// A global table of PyTypeObject to be stored at the top of interpreter
// so that each module can retrieve the PyTypeObject of types wrapped by other modules.
namespace c2py {

  // Table : c++ type name -> PyTypeObject *
  using pto_table_t = std::map<std::string, PyTypeObject *>;

  // Get the PyTypeObject table, initialize it if necessary
  std::shared_ptr<pto_table_t> get_pto_table();

  // Each translation holds a shared pointer to the PyTypeObject table
  static std::shared_ptr<pto_table_t> conv_table_sptr = get_pto_table(); //NOLINT

  // get the PyTypeObject from the table in __main__.
  // if the type was not wrapped, return nullptr and set up a Python exception
  PyTypeObject *get_type_ptr(std::type_index const &ind);

  // get the PyTypeObject from the table in __main__.
  template <typename T> void add_type_object_to_main(const char *pyname, PyObject *_main_, pto_table_t &conv_table) {
    c2py::wrap_pytype<T>.tp_doc = c2py::tp_doc<T>.data();
    Py_INCREF(&c2py::wrap_pytype<T>);
    PyModule_AddObject(_main_, pyname, (PyObject *)&c2py::wrap_pytype<T>);
    conv_table[std::type_index(typeid(T)).name()] = &c2py::wrap_pytype<T>;
  }

  //---------------------  wrapped type -----------------------------

  template <typename T>
    requires(is_wrapped<T>)
  struct py_converter<T> {

    static_assert(not std::is_reference_v<T>); // The T = U& case is a separate specialization

    template <typename U> static PyObject *c2py(U &&x) {
      PyTypeObject *p = get_type_ptr(typeid(T));
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
      PyTypeObject *p = get_type_ptr(typeid(T));
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
      PyTypeObject *p = get_type_ptr(typeid(T));
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

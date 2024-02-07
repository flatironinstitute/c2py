#pragma once
#include "../py_converter.hpp"
#include "../pytypes/wrap.hpp"

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

  //---------------------  wrapped type -----------------------------

  template <typename T>
    requires(is_wrapped<T>)
  struct py_converter<T> { // hence T , T &, T const & for T wrapped.

    using wrap = struct {
      PyObject_HEAD //
         T *_c;
    };

    using is_wrapped = void; // to recognize
    static_assert(not std::is_reference_v<T>, "Not implemented");

    template <typename U> static PyObject *c2py(U &&x) {
      PyTypeObject *p = get_type_ptr(typeid(T));
      if (p == nullptr) return nullptr;
      auto *self = (wrap *)p->tp_alloc(p, 0);
      if (self != NULL) { self->_c = new T{std::forward<U>(x)}; } // NOLINT
      return (PyObject *)self;
    }

    static T &py2c(PyObject *ob) {
      auto *_c = ((wrap *)ob)->_c;
      if (_c == NULL) {
        std::cerr << "Severe internal error : _c is null in py2c\n";
        std::terminate();
      }
      return *_c;
    }

    static bool is_convertible(PyObject *ob, bool raise_exception) {
      PyTypeObject *p = get_type_ptr(typeid(T));
      if (p == nullptr) return false;
      if (PyObject_TypeCheck(ob, p)) {
        if (((wrap *)ob)->_c != NULL) return true;
        auto err = std::string{"Severe internal error : Python object of "} + p->tp_name + " has a _c NULL pointer !!";
        if (raise_exception) PyErr_SetString(PyExc_TypeError, err.c_str());
        return false;
      }
      auto err = std::string{"Python object is not a "} + p->tp_name + " but a " + Py_TYPE(ob)->tp_name;
      if (raise_exception) PyErr_SetString(PyExc_TypeError, err.c_str());
      return false;
    }
  };

} // namespace c2py

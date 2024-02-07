#pragma once
#include <sstream>

#include "../util/str.hpp"
#include "../cpp_name.hpp"
#include "../py_converter.hpp"

// local pieces, separated for code readibility
#include "arithmetic.hpp"
#include "iterator.hpp"
#include "specialmethods.hpp"

namespace c2py {

  // ---------------  The generic wrapped type --------------------
  template <typename T> struct wrap {
    PyObject_HEAD //;
       T *_c;
  };

  // ============ Prepare all the slots for wrap_pytype below ====================
  // tp_new
  template <typename T> static PyObject *tp_new(PyTypeObject *type, PyObject * /*args*/, PyObject * /*kwds*/) {
    auto *self = (wrap<T> *)type->tp_alloc(type, 0);
    if (self != NULL) self->_c = NULL;
    return (PyObject *)self;
  }

  // tp_dealloc
  template <typename T> static void tp_dealloc(PyObject *self) {
    auto *c_ptr = ((wrap<T> *)self)->_c;
    if (c_ptr != NULL) delete c_ptr; // NOLINT should never be null, but I protect it anyway
    Py_TYPE(self)->tp_free((PyObject *)self);
  }

  template <typename T> static constexpr initproc tp_init   = nullptr;
  template <typename T> static constexpr char *tp_name      = nullptr; //NOLINT
  template <typename T> static constexpr const char *tp_doc = nullptr;
  template <typename T> static PyObject *tp_repr(PyObject *self); // impl below
  template <typename T> static PyObject *tp_str(PyObject *self) { return tp_repr<T>(self); }
  template <typename T> static constinit PyMappingMethods tp_as_mapping = {nullptr, nullptr, nullptr}; //NOLINT
  template <typename T> static constexpr ternaryfunc tp_call            = nullptr;
  template <typename T> static constinit PyMethodDef tp_methods[]       = {{nullptr, nullptr, 0, nullptr}}; //NOLINT
  template <typename T> static constexpr PyGetSetDef *tp_getset         = {nullptr};                        //NOLINT
  // template <typename Cls> static PyObject *tp_richcompare(PyObject *a, PyObject *b, int op);

  // --------------- The corresponding python object : wrap_pytype --------------------

  template <typename T>
  static constinit PyTypeObject wrap_pytype = // NOLINT
     {
        PyVarObject_HEAD_INIT(NULL, 0)            //
        tp_name<T>,                               // tp_name
        sizeof(wrap<T>),                          // tp_basicsize
        0,                                        // tp_itemsize
        (destructor)tp_dealloc<T>,                // tp_dealloc
        0,                                        // tp_vectorcall_offset
        0,                                        // tp_getattr
        0,                                        // tp_setattr
        0,                                        // tp_as_async
        &tp_repr<T>,                              // tp_repr
        tp_as_number<T>,                          // tp_as_number
        0,                                        // tp_as_sequence
        &tp_as_mapping<T>,                        // tp_as_mapping
        0,                                        // tp_hash
        tp_call<T>,                               // tp_call
        &tp_str<T>,                               // tp_str
        0,                                        // tp_getattro
        0,                                        // tp_setattro
        0,                                        // tp_as_buffer
        Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, // tp_flags
        tp_doc<T>,                                // tp_doc
        0,                                        // tp_traverse
        0,                                        // tp_clear
        &tp_richcompare<T>,                       // tp_richcompare
        0,                                        // tp_weaklistoffset
        tp_iter<T>,                               // tp_iter
        0,                                        // tp_iternext
        tp_methods<T>,                            // tp_methods
        0,                                        // tp_members
        tp_getset<T>,                             // tp_getset
        0,                                        // tp_base
        0,                                        // tp_dict
        0,                                        // tp_descr_get
        0,                                        // tp_descr_set
        0,                                        // tp_dictoffset
        (initproc)tp_init<T>,                     // tp_init
        0,                                        // tp_alloc
        (newfunc)tp_new<T>,                       // tp_new
        0,                                        // tp_free
        0,                                        // tp_is_gc
        0,                                        // tp_bases
        0,                                        // tp_mro
        0,                                        // [tp_cache
        0,                                        // tp_subclasses
        0,                                        // tp_weaklist
        0,                                        // tp_del
        0,                                        // tp_version_tag
        0,                                        // tp_finalize
        0,                                        // tp_vectorcall
#if (PY_MINOR_VERSION >= 12)
        0, // tp_watched
#endif
  };

  // --------------------- implementations ----------------------
  // the implementations that require wrap_pytype must be here.

  // tp_repr
  // if C++ has << operator, we use it, if not put some generic string
  template <typename Cls> static PyObject *tp_repr(PyObject *self) {
    if constexpr (requires(Cls const &x) { std::stringstream{} << x; }) {
      auto &self_c = py_converter<Cls>::py2c(self);
      std::stringstream fs;
      fs << self_c;
      return PyUnicode_FromString(fs.str().c_str());
    } else {
      auto s = wrap_pytype<Cls>.tp_name + " [wrapped from C++ object "s + cpp_name<Cls> + "]";
      return PyUnicode_FromString(s.c_str());
    }
  }

} // namespace c2py

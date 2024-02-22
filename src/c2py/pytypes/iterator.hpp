#pragma once
//https://en.cppreference.com/w/cpp/ranges/range
#include <ranges>
#include "../py_converter.hpp"
#include "../converters/basic_types.hpp"
namespace c2py {

  // *******************************************
  //  py_iterator
  //  a Python type which erases a pair of iterators
  // *******************************************

  template <typename Iterator, typename Sentinel> struct py_iterator { // NOLINT
    PyObject_HEAD                                                      //;
       PyObject *container = nullptr;
    Iterator iter;
    Sentinel end;
  };

  // ---------------------------------------

  template <typename Iterator, typename Sentinel> static void py_iterator_dealloc(py_iterator<Iterator, Sentinel> *self) {
    Py_XDECREF(self->container);
    Py_TYPE(self)->tp_free((PyObject *)self);
  }

  // ---------------------------------------

  // the __iter__ of the iterator type : returns itself
  template <typename Iterator, typename Sentinel> PyObject *tp_iter_iterator(PyObject *self) {
    Py_INCREF(self);
    return self;
  }

  // ---------------------------------------
  // the next() method of the iterator
  template <typename Iterator, typename Sentinel> PyObject *tp_iterator_iternext(PyObject *self) {
    auto *self_c = (py_iterator<Iterator, Sentinel> *)self;
    if (!(self_c->iter == self_c->end)) {
      PyObject *res = cxx2py(*(self_c->iter)); // make a COPY, I cannot wrap a ref in python !
      ++self_c->iter;
      return res;
    } else {
      PyErr_SetNone(PyExc_StopIteration);
      return nullptr;
    }
  }

  // ---------------------------------------

  template <typename Iterator, typename Sentinel>
  static PyTypeObject py_iterator_type_object = // NOLINT
     {
        PyVarObject_HEAD_INIT(nullptr, 0)                    //
        "Iterator",                                          // tp_name
        sizeof(py_iterator<Iterator, Sentinel>),             // tp_basicsize
        0,                                                   // tp_itemsize
        (destructor)py_iterator_dealloc<Iterator, Sentinel>, // tp_dealloc
        0,                                                   // tp_print
        0,                                                   // tp_getattr
        0,                                                   // tp_setattr
        0,                                                   // tp_compare
        0,                                                   // tp_repr
        0,                                                   // tp_as_number
        0,                                                   // tp_as_sequence
        0,                                                   // tp_as_mapping
        0,                                                   // tp_hash
        0,                                                   // tp_call
        0,                                                   // tp_str
        0,                                                   // tp_getattro
        0,                                                   // tp_setattro
        0,                                                   // tp_as_buffer
        Py_TPFLAGS_DEFAULT,                                  // tp_flags
        "C++ Iterator",                                      // tp_doc
        0,                                                   // tp_traverse
        0,                                                   // tp_clear
        0,                                                   // tp_richcompare
        0,                                                   // tp_weaklistoffset
        tp_iter_iterator<Iterator, Sentinel>,                // tp_iter: __iter__() method
        tp_iterator_iternext<Iterator, Sentinel>,            // tp_iternext: next() method
        0,                                                   // tp_methods
        0,                                                   // tp_members
        0,                                                   // tp_getset
        0,                                                   // tp_base
        0,                                                   // tp_dict
        0,                                                   // tp_descr_get
        0,                                                   // tp_descr_set
        0,                                                   // tp_dictoffset
        0,                                                   // tp_init
        0,                                                   // tp_alloc
        0,                                                   // tp_new
        0,                                                   // tp_free
        0,                                                   // tp_is_gc
        0,                                                   // tp_bases
        0,                                                   // tp_mro
        0,                                                   // [tp_cache
        0,                                                   // tp_subclasses
        0,                                                   // tp_weaklist
        0,                                                   // tp_del
        0,                                                   // tp_version_tag
        0,                                                   // tp_finalize
        0,                                                   // tp_vectorcall
  };

  // ---------------------------------------

  // make a py_iterator<Iterator, Sentinel> from a begin, end.
  template <typename Iterator, typename Sentinel> PyObject *make_iterator(Iterator b, Sentinel e, PyObject *parent = nullptr) {
    auto &pytype            = py_iterator_type_object<Iterator, Sentinel>;
    static bool initialized = false;
    if (not initialized) { // once per couple of <Iterator, Sentinel>
      pytype.tp_new = PyType_GenericNew;
      if (PyType_Ready(&pytype) < 0) return nullptr;
      Py_INCREF(&pytype);
      initialized = true;
    }
    // Allocate and init it by hand (no init method), it can only be constructed from C
    using r_t = py_iterator<Iterator, Sentinel>;
    r_t *p    = PyObject_New(r_t, &pytype);
    if (!p) return nullptr;
    p->container = parent;
    // We keep an owned reference to the container object (e.g. [x for x in g.mesh],
    // if the container is a temporary and the iterator lives longer than its python reference).
    Py_XINCREF(parent);
    std::ignore = new ((void *)(&p->iter)) decltype(p->iter); // NOLINT
    std::ignore = new ((void *)(&p->end)) decltype(p->end);   // NOLINT
    p->iter     = std::move(b);
    p->end      = std::move(e);
    return (PyObject *)p;
  }

  // *******************************************
  //  implement tp_iter
  // *******************************************

  // the __iter__ of the main type: return a new iterator.
  template <typename T> PyObject *tp_iter_impl(PyObject *self) {
    static_assert(std::ranges::range<T>);
    decltype(auto) self_c = py2cxx<T>(self);
    using std::begin;
    using std::end;
    return make_iterator(begin(self_c), end(self_c), self);
  }

  // ---------------------------------------

  template <typename T>
  static constexpr getiterfunc tp_iter = []() {
    if constexpr (std::ranges::range<T>) // FIXME : add convertibility of the iterator value
      return &tp_iter_impl<T>;
    else
      return (getiterfunc) nullptr;
  }();

} // namespace c2py

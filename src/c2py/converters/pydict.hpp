#pragma once
#include "../py_converter.hpp"
#include "../pydict.hpp"

namespace c2py {

  template <> struct py_converter<pydict> {
    static PyObject *c2py(pydict d) { return d.new_ref(); }
    static bool is_convertible(PyObject *ob, bool raise_exception) {
      bool r = PyDict_Check(ob);
      if (r) return true;
      if (raise_exception) PyErr_SetString(PyExc_TypeError, ("Object is not a dictionary"));
      return false;
    }
    static pydict py2c(PyObject *ob) { return {pyref::borrowed(ob)}; }
  };

} // namespace c2py

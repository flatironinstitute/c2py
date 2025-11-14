#include <c2py/c2py.hpp>
#include <Python.h>

#include <string>

PyObject *pyobject_ptr(double x) { return PyFloat_FromDouble(x); }
c2py::pyref pyref_obj(double x) { return PyFloat_FromDouble(x); }

#include "refcount.wrap.cxx"

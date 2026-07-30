// Functions taking and returning a L, and nothing else : this module registers no Python type for
// L. Its conversions therefore resolve to whatever type another module has registered, which is what
// the tests of this directory observe.

#include "L.hpp"

static L make_L(int k) { return L{k}; }
static int get_k(L const &l) { return l.k; }
static void bump(L &l) { l.k += 1; } // takes a L & : goes through py_converter<L>::is_const

static auto const _fun_make_L = c2py::dispatcher_f_kw_t{c2py::cfun([](int k) { return make_L(k); }, "k")};
static auto const _fun_get_k  = c2py::dispatcher_f_kw_t{c2py::cfun([](L const &l) { return get_k(l); }, "l")};
static auto const _fun_bump   = c2py::dispatcher_f_kw_t{c2py::cfun([](L &l) { return bump(l); }, "l")};

// A reference to a L, wrapped with a guardian : this is what the generated code does for a method
// returning a L&.
static PyObject *wrap_ref_to_L(PyObject *self, PyObject * /*unused*/) {
  static L l{7}; // NOLINT
  return c2py::py_converter<L &>::c2py(l, self);
}

static PyMethodDef module_methods[] = {
   {"make_L", (PyCFunction)c2py::pyfkw<_fun_make_L>, METH_VARARGS | METH_KEYWORDS, "Make a L"},
   {"get_k", (PyCFunction)c2py::pyfkw<_fun_get_k>, METH_VARARGS | METH_KEYWORDS, "Read k, taking a L const &"},
   {"bump", (PyCFunction)c2py::pyfkw<_fun_bump>, METH_VARARGS | METH_KEYWORDS, "Increase k, taking a L &"},
   {"wrap_ref_to_L", (PyCFunction)wrap_ref_to_L, METH_NOARGS, "Try to wrap a L &"},
   {NULL} // Sentinel
};

static struct PyModuleDef module_def = {PyModuleDef_HEAD_INIT, "use_L", "Functions on L, registering nothing", -1, module_methods};

extern "C" __attribute__((visibility("default"))) PyObject *PyInit_use_L() { return PyModule_Create(&module_def); }

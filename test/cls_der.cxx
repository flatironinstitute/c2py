#pragma GCC visibility push(hidden)
//#pragma CLANG visibility push(hidden)
#ifdef __clang__
#pragma clang diagnostic push
//#pragma clang diagnostic ignored "-W#warnings"
#pragma clang diagnostic ignored "-Wmissing-field-initializers"
#endif

//#pragma clang diagnostic pop

//#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION

// C.f. https://numpy.org/doc/1.21/reference/c-api/array.html#importing-the-api
#define PY_ARRAY_UNIQUE_SYMBOL _cpp2py_ARRAY_API
#include "c2py/c2py.hpp"
//#include "c2py/module.hpp"
//#include "c2py/serialization.hpp"

#include "cls_der.cpp"

using namespace c2py;
using c2py::operator"" _a;

template <> constexpr bool c2py::is_wrapped<A> = true;
template <> constexpr bool c2py::is_wrapped<B> = true;

// =============== struct A =====================
namespace c2py {
  template <> inline const std::string cpp_name<A> = "[C++ A]";
  template <> constexpr auto tp_name<A>            = "cls_der.A";
  template <> constexpr const char *tp_doc<A>      = "Doc A";
} // namespace c2py
//      --- constructor ---
static int init_a(PyObject *self, PyObject *args, PyObject *kwargs) {
  static dispatcher_c_kw_t ovs = {c_constructor<A>()};
  return ovs(self, args, kwargs);
};

template <> constexpr initproc c2py::tp_init<A> = &init_a;

static const auto fun_A = dispatcher_f_kw_t{cfun(c2py::castm<int, int>(&A::a), "x", "y")};

//  --- method table ---
template <>
PyMethodDef c2py::tp_methods<A>[] = {
   {"a", (PyCFunction)c2py::pyfkw<fun_A>, METH_VARARGS | METH_KEYWORDS, "BLABLA"}, // put doc out if too long
   {NULL}                                                                          // Sentinel
};

// =============== struct B =====================
namespace c2py {
  template <> inline const std::string cpp_name<B> = "[C++ B]";
  template <> constexpr auto tp_name<B>            = "cls_der.B";
  template <> constexpr const char *tp_doc<B>      = "Doc B";
} // namespace c2py
//      --- constructor ---
static int init_b(PyObject *self, PyObject *args, PyObject *kwargs) {
  static dispatcher_c_kw_t ovs = {c_constructor<B>()};
  return ovs(self, args, kwargs);
};

template <> constexpr initproc c2py::tp_init<B> = &init_b;

static const auto fun_B = dispatcher_f_kw_t{cfun(c2py::castm<int>(&B::b), "i")};

//  --- method table ---
template <>
PyMethodDef c2py::tp_methods<B>[] = {
   {"b", (PyCFunction)c2py::pyfkw<fun_B>, METH_VARARGS | METH_KEYWORDS, "BLABLA"}, // put doc out if too long
   {NULL}                                                                          // Sentinel
};

//--------------------- module function table  -----------------------------

static PyMethodDef module_methods[] = {
   {NULL} // Sentinel
};

//--------------------- module struct & init error definition ------------

//// module doc directly in the code or "" if not present...
/// Or mandatory ?
static struct PyModuleDef module_def = {PyModuleDef_HEAD_INIT, "cls_der", /* name of module */
                                        "DOC MODULE",                     /* module documentation, may be NULL */
                                        -1, /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
                                        module_methods};

//--------------------- defines ---------------------

//--------------------- module init function -----------------------------

extern "C" __attribute__((visibility("default"))) PyObject *PyInit_cls_der() {

  // import numpy iff 'numpy/arrayobject.h' included
#ifdef Py_ARRAYOBJECT_H
  import_array();
#endif

  PyObject *m;

  if (PyType_Ready(&py_type_object<B>) < 0) return NULL;
  py_type_object<B>.tp_new = PyType_GenericNew;

  py_type_object<A>.tp_base = &py_type_object<B>;

  if (PyType_Ready(&py_type_object<A>) < 0) return NULL;
  py_type_object<A>.tp_new = PyType_GenericNew;

  m = PyModule_Create(&module_def);
  if (m == NULL) return NULL;

  auto &conv_table = *c2py::conv_table_sptr.get();

  CLAIR_C2PY_ADD_TYPE_OBJECT(A, "A");
  CLAIR_C2PY_ADD_TYPE_OBJECT(B, "B");

  return m;
}


// C.f. https://numpy.org/doc/1.21/reference/c-api/array.html#importing-the-api
#define PY_ARRAY_UNIQUE_SYMBOL _cpp2py_ARRAY_API
#ifdef __clang__
// #pragma clang diagnostic ignored "-W#warnings"
#endif
#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#pragma GCC diagnostic ignored "-Wcast-function-type"
#pragma GCC diagnostic ignored "-Wcpp"
#endif

#define C2PY_VERSION_MAJOR 0
#define C2PY_VERSION_MINOR 1

#include "c2py/c2py.hpp"
#include "two_module_2.cpp"

using c2py::operator"" _a;

// ==================== Wrapped classes =====================

#ifndef C2PY_HXX_DECLARATION_two_module_2_GUARDS
#define C2PY_HXX_DECLARATION_two_module_2_GUARDS
template <> constexpr bool c2py::is_wrapped<B> = true;
#endif

// ==================== enums =====================

// ==================== module classes =====================

template <> inline const std::string c2py::cpp_name<B>   = "B";
template <> inline constexpr auto c2py::tp_name<B>       = "two_module_2.B";
template <> inline constexpr const char *c2py::tp_doc<B> = R"DOC(   )DOC";

static auto init_0                              = c2py::dispatcher_c_kw_t{c2py::c_constructor<B>()};
template <> constexpr initproc c2py::tp_init<B> = c2py::pyfkw_constructor<init_0>;
// g
static auto const fun_0   = c2py::dispatcher_f_kw_t{c2py::cfun(c2py::castm<int, const N::A &>(&B::g), "i", "a")};
static const auto doc_d_0 = fun_0.doc({R"DOC(   )DOC"});

// ----- Method table ----
template <>
PyMethodDef c2py::tp_methods<B>[] = {
   {"g", (PyCFunction)c2py::pyfkw<fun_0>, METH_VARARGS | METH_KEYWORDS, doc_d_0.c_str()},
   {nullptr, nullptr, 0, nullptr} // Sentinel
};

// ----- Method table ----

template <>
constinit PyGetSetDef c2py::tp_getset<B>[] = {

   {nullptr, nullptr, nullptr, nullptr, nullptr}};

// ==================== module functions ====================

//--------------------- module function table  -----------------------------

static PyMethodDef module_methods[] = {
   {nullptr, nullptr, 0, nullptr} // Sentinel
};

//--------------------- module struct & init error definition ------------

//// module doc directly in the code or "" if not present...
/// Or mandatory ?
static struct PyModuleDef module_def = {PyModuleDef_HEAD_INIT,
                                        "two_module_2",    /* name of module */
                                        R"RAWDOC()RAWDOC", /* module documentation, may be NULL */
                                        -1, /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
                                        module_methods,
                                        NULL,
                                        NULL,
                                        NULL,
                                        NULL};

//--------------------- module init function -----------------------------

extern "C" __attribute__((visibility("default"))) PyObject *PyInit_two_module_2() {

  if (not c2py::check_python_version()) return NULL;

    // import numpy iff 'numpy/arrayobject.h' included
#ifdef Py_ARRAYOBJECT_H
  import_array();
#endif

  PyObject *m;

  if (PyType_Ready(&c2py::wrap_pytype<c2py::py_range>) < 0) return NULL;
  if (PyType_Ready(&c2py::wrap_pytype<B>) < 0) return NULL;

  m = PyModule_Create(&module_def);
  if (m == NULL) return NULL;

  auto &conv_table = *c2py::conv_table_sptr.get();

  conv_table[std::type_index(typeid(c2py::py_range)).name()] = &c2py::wrap_pytype<c2py::py_range>;
  CLAIR_C2PY_ADD_TYPE_OBJECT(B, "B");

  return m;
}


// C.f. https://numpy.org/doc/1.21/reference/c-api/array.html#importing-the-api
#define PY_ARRAY_UNIQUE_SYMBOL _cpp2py_ARRAY_API
#ifndef CLAIR_C2PY_WRAP_GEN
#ifdef __clang__
// #pragma clang diagnostic ignored "-W#warnings"
#endif
#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#pragma GCC diagnostic ignored "-Wcast-function-type"
#pragma GCC diagnostic ignored "-Wcpp"
#endif

#define C2PY_VERSION_MAJOR 1
#define C2PY_VERSION_MINOR 0

#include <c2py/c2py.hpp>
#include <c2py/version_check.hpp>

using c2py::operator""_a;

// ==================== enums =====================

// ==================== module classes =====================

// ==================== module functions ====================

// f_map
static auto const _c2py_fun_6119ff9c = c2py::dispatcher_f_kw_t{c2py::cfun([](std::map<std::string, int> m) { return f_map(m); }, "m")};

// f_optional
static auto const _c2py_fun_2773917a = c2py::dispatcher_f_kw_t{c2py::cfun([](bool present) { return f_optional(present); }, "present")};

// f_string
static auto const _c2py_fun_32a6c98b = c2py::dispatcher_f_kw_t{c2py::cfun([](std::string s) { return f_string(s); }, "s")};

// f_tuple
static auto const _c2py_fun_f22cdf54 = c2py::dispatcher_f_kw_t{c2py::cfun([]() { return f_tuple(); })};

// f_vector
static auto const _c2py_fun_ec878e99 = c2py::dispatcher_f_kw_t{c2py::cfun([](std::vector<int> v) { return f_vector(v); }, "v")};

static const auto _c2py_doc_6119ff9c = _c2py_fun_6119ff9c.doc(R"DOC()DOC");
static const auto _c2py_doc_2773917a = _c2py_fun_2773917a.doc(R"DOC()DOC");
static const auto _c2py_doc_32a6c98b = _c2py_fun_32a6c98b.doc(R"DOC()DOC");
static const auto _c2py_doc_f22cdf54 = _c2py_fun_f22cdf54.doc(R"DOC()DOC");
static const auto _c2py_doc_ec878e99 = _c2py_fun_ec878e99.doc(R"DOC()DOC");
//--------------------- module function table  -----------------------------

// clang-format off
static PyMethodDef module_methods[] = {
   PMDF("f_map", 6119ff9c),
   PMDF("f_optional", 2773917a),
   PMDF("f_string", 32a6c98b),
   PMDF("f_tuple", f22cdf54),
   PMDF("f_vector", ec878e99),
   {nullptr, nullptr, 0, nullptr}  // Sentinel
};
// clang-format on

//--------------------- module struct & init error definition ------------

//// module doc directly in the code or "" if not present...
/// Or mandatory ?
static struct PyModuleDef module_def = {PyModuleDef_HEAD_INIT,
                                        "std_container",   /* name of module */
                                        R"RAWDOC()RAWDOC", /* module documentation, may be NULL */
                                        -1, /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
                                        module_methods,
                                        NULL,
                                        NULL,
                                        NULL,
                                        NULL};

//--------------------- module init function -----------------------------

extern "C" __attribute__((visibility("default"))) PyObject *PyInit_std_container() {

  if (not c2py::check_python_version("std_container")) return NULL;

  // import numpy iff 'numpy/arrayobject.h' included
#ifdef Py_ARRAYOBJECT_H
  import_array();
#endif

  PyObject *m;

  m = PyModule_Create(&module_def);
  if (m == NULL) return NULL;

  if (not c2py::register_internal_types()) return NULL;
#define _add_type(T, N)                                                                                                                              \
  if (not c2py::add_type_object_to_main<T>(N, m)) return NULL

#undef _add_type

  return m;
}
#endif
// CLAIR_WRAP_GEN

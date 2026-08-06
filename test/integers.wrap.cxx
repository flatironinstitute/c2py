
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

// add_int16
static auto const _c2py_fun_7ae957fd = c2py::dispatcher_f_kw_t{c2py::cfun([](int16_t a, int16_t b) { return add_int16(a, b); }, "a", "b")};

// identity_int16
static auto const _c2py_fun_31c6f06e = c2py::dispatcher_f_kw_t{c2py::cfun([](int16_t x) { return identity_int16(x); }, "x")};

// identity_int32
static auto const _c2py_fun_9dcc17a0 = c2py::dispatcher_f_kw_t{c2py::cfun([](int32_t x) { return identity_int32(x); }, "x")};

// identity_int64
static auto const _c2py_fun_31c4b1d7 = c2py::dispatcher_f_kw_t{c2py::cfun([](int64_t x) { return identity_int64(x); }, "x")};

// identity_int64_with_defarg
static auto const _c2py_fun_f59ddf00 = c2py::dispatcher_f_kw_t{c2py::cfun([](int64_t x) { return identity_int64_with_defarg(x); }, "x"_a = 42)};

// identity_uint16
static auto const _c2py_fun_52ba256b = c2py::dispatcher_f_kw_t{c2py::cfun([](uint16_t x) { return identity_uint16(x); }, "x")};

// identity_uint32
static auto const _c2py_fun_c6bf5935 = c2py::dispatcher_f_kw_t{c2py::cfun([](uint32_t x) { return identity_uint32(x); }, "x")};

// identity_uint64
static auto const _c2py_fun_42b35076 = c2py::dispatcher_f_kw_t{c2py::cfun([](uint64_t x) { return identity_uint64(x); }, "x")};

// identity_uint64_with_defarg
static auto const _c2py_fun_bc2a7f29 = c2py::dispatcher_f_kw_t{c2py::cfun([](uint64_t x) { return identity_uint64_with_defarg(x); }, "x"_a = 42)};

static const auto _c2py_doc_7ae957fd = _c2py_fun_7ae957fd.doc(R"DOC()DOC");
static const auto _c2py_doc_31c6f06e = _c2py_fun_31c6f06e.doc(R"DOC()DOC");
static const auto _c2py_doc_9dcc17a0 = _c2py_fun_9dcc17a0.doc(R"DOC()DOC");
static const auto _c2py_doc_31c4b1d7 = _c2py_fun_31c4b1d7.doc(R"DOC()DOC");
static const auto _c2py_doc_f59ddf00 = _c2py_fun_f59ddf00.doc(R"DOC()DOC");
static const auto _c2py_doc_52ba256b = _c2py_fun_52ba256b.doc(R"DOC()DOC");
static const auto _c2py_doc_c6bf5935 = _c2py_fun_c6bf5935.doc(R"DOC()DOC");
static const auto _c2py_doc_42b35076 = _c2py_fun_42b35076.doc(R"DOC()DOC");
static const auto _c2py_doc_bc2a7f29 = _c2py_fun_bc2a7f29.doc(R"DOC()DOC");
//--------------------- module function table  -----------------------------

// clang-format off
static PyMethodDef module_methods[] = {
   PMDF("add_int16", 7ae957fd),
   PMDF("identity_int16", 31c6f06e),
   PMDF("identity_int32", 9dcc17a0),
   PMDF("identity_int64", 31c4b1d7),
   PMDF("identity_int64_with_defarg", f59ddf00),
   PMDF("identity_uint16", 52ba256b),
   PMDF("identity_uint32", c6bf5935),
   PMDF("identity_uint64", 42b35076),
   PMDF("identity_uint64_with_defarg", bc2a7f29),
   {nullptr, nullptr, 0, nullptr}  // Sentinel
};
// clang-format on

//--------------------- module struct & init error definition ------------

//// module doc directly in the code or "" if not present...
/// Or mandatory ?
static struct PyModuleDef module_def = {PyModuleDef_HEAD_INIT,
                                        "integers",        /* name of module */
                                        R"RAWDOC()RAWDOC", /* module documentation, may be NULL */
                                        -1, /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
                                        module_methods,
                                        NULL,
                                        NULL,
                                        NULL,
                                        NULL};

//--------------------- module init function -----------------------------

extern "C" __attribute__((visibility("default"))) PyObject *PyInit_integers() {

  if (not c2py::check_python_version("integers")) return NULL;

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

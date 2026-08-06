
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

using c2py::operator""_a;

// ==================== enums =====================

// ==================== module classes =====================

// ==================== module functions ====================

// call1
static auto const _c2py_fun_dd33bb48 = c2py::dispatcher_f_kw_t{c2py::cfun([](const std::function<int(int, int)> &f) { return call1(f); }, "f")};

// call2
static auto const _c2py_fun_e033c001 = c2py::dispatcher_f_kw_t{c2py::cfun([](std::function<int(int, int)> f) { return call2(f); }, "f")};

// call3
static auto const _c2py_fun_df33be6e =
   c2py::dispatcher_f_kw_t{c2py::cfun([](const std::function<int(std::pair<int, int>)> &f) { return call3(f); }, "f")};

// call4
static auto const _c2py_fun_e233c327 = c2py::dispatcher_f_kw_t{c2py::cfun([](std::function<int(std::pair<int, int>)> f) { return call4(f); }, "f")};

// call5
static auto const _c2py_fun_e133c194 =
   c2py::dispatcher_f_kw_t{c2py::cfun([](std::function<int(const std::pair<int, int> &)> f) { return call5(f); }, "f")};

// callback
static auto const _c2py_fun_87f03406 = c2py::dispatcher_f_kw_t{c2py::cfun([]() { return callback(); })};

// make_f
static auto const _c2py_fun_97dddf82 = c2py::dispatcher_f_kw_t{c2py::cfun([]() { return make_f(); })};

// make_f2
static auto const _c2py_fun_c2472210 = c2py::dispatcher_f_kw_t{c2py::cfun([]() { return make_f2(); })};

static const auto _c2py_doc_dd33bb48 = _c2py_fun_dd33bb48.doc(R"DOC()DOC");
static const auto _c2py_doc_e033c001 = _c2py_fun_e033c001.doc(R"DOC()DOC");
static const auto _c2py_doc_df33be6e = _c2py_fun_df33be6e.doc(R"DOC()DOC");
static const auto _c2py_doc_e233c327 = _c2py_fun_e233c327.doc(R"DOC()DOC");
static const auto _c2py_doc_e133c194 = _c2py_fun_e133c194.doc(R"DOC()DOC");
static const auto _c2py_doc_87f03406 = _c2py_fun_87f03406.doc(R"DOC()DOC");
static const auto _c2py_doc_97dddf82 = _c2py_fun_97dddf82.doc(R"DOC()DOC");
static const auto _c2py_doc_c2472210 = _c2py_fun_c2472210.doc(R"DOC()DOC");
//--------------------- module function table  -----------------------------

// clang-format off
static PyMethodDef module_methods[] = {
   PMDF("call1", dd33bb48),
   PMDF("call2", e033c001),
   PMDF("call3", df33be6e),
   PMDF("call4", e233c327),
   PMDF("call5", e133c194),
   PMDF("callback", 87f03406),
   PMDF("make_f", 97dddf82),
   PMDF("make_f2", c2472210),
   {nullptr, nullptr, 0, nullptr}  // Sentinel
};
// clang-format on

//--------------------- module struct & init error definition ------------

//// module doc directly in the code or "" if not present...
/// Or mandatory ?
static struct PyModuleDef module_def = {PyModuleDef_HEAD_INIT,
                                        "callables",       /* name of module */
                                        R"RAWDOC()RAWDOC", /* module documentation, may be NULL */
                                        -1, /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
                                        module_methods,
                                        NULL,
                                        NULL,
                                        NULL,
                                        NULL};

//--------------------- module init function -----------------------------

extern "C" __attribute__((visibility("default"))) PyObject *PyInit_callables() {

  if (not c2py::check_python_version("callables")) return NULL;

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

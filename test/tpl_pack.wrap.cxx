
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

// deduced_after_pack
static auto const _c2py_fun_ec70254e = c2py::dispatcher_f_kw_t{c2py::cfun([](int g) { return deduced_after_pack<0>(g); }, "g"),
                                                               c2py::cfun([](double g) { return deduced_after_pack<0>(g); }, "g")};

// fn_param_pack
static auto const _c2py_fun_a3614ad1 = c2py::dispatcher_f_kw_t{
   c2py::cfun([](int g) { return fn_param_pack<int>(g); }, "g"),
   c2py::cfun([](int g, double args) { return fn_param_pack<int, double>(g, args); }, "g", "args"),
   c2py::cfun([](int g, double args0, char args1) { return fn_param_pack<int, double, char>(g, args0, args1); }, "g", "args0", "args1")};

static const auto _c2py_doc_ec70254e = _c2py_fun_ec70254e.doc(R"DOC()DOC");
static const auto _c2py_doc_a3614ad1 = _c2py_fun_a3614ad1.doc(R"DOC()DOC");
//--------------------- module function table  -----------------------------

// clang-format off
static PyMethodDef module_methods[] = {
   PMDF("deduced_after_pack", ec70254e),
   PMDF("fn_param_pack", a3614ad1),
   {nullptr, nullptr, 0, nullptr}  // Sentinel
};
// clang-format on

//--------------------- module struct & init error definition ------------

//// module doc directly in the code or "" if not present...
/// Or mandatory ?
static struct PyModuleDef module_def = {PyModuleDef_HEAD_INIT,
                                        "tpl_pack",        /* name of module */
                                        R"RAWDOC()RAWDOC", /* module documentation, may be NULL */
                                        -1, /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
                                        module_methods,
                                        NULL,
                                        NULL,
                                        NULL,
                                        NULL};

//--------------------- module init function -----------------------------

extern "C" __attribute__((visibility("default"))) PyObject *PyInit_tpl_pack() {

  if (not c2py::check_python_version("tpl_pack")) return NULL;

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

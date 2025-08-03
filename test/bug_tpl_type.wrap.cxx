
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

#define C2PY_VERSION_MAJOR 0
#define C2PY_VERSION_MINOR 1

#include <c2py/c2py.hpp>

using c2py::operator""_a;

// ==================== Wrapped classes =====================

template <> constexpr bool c2py::is_wrapped<C>      = true;
template <> constexpr bool c2py::is_wrapped<A<3>>   = true;
template <> constexpr bool c2py::is_wrapped<B<int>> = true;

// ==================== enums =====================

// ==================== module classes =====================

template <> inline constexpr auto c2py::tp_name<C>       = "bug_tpl_type.C";
template <> inline constexpr const char *c2py::tp_doc<C> = R"DOC(   )DOC";

static auto init_0                              = c2py::dispatcher_c_kw_t{c2py::c_constructor<C>()};
template <> constexpr initproc c2py::tp_init<C> = c2py::pyfkw_constructor<init_0>;

// ----- Method table ----
template <>
PyMethodDef c2py::tp_methods<C>[] = {

   {nullptr, nullptr, 0, nullptr} // Sentinel
};

// ----- Method table ----

template <>
constinit PyGetSetDef c2py::tp_getset<C>[] = {

   {nullptr, nullptr, nullptr, nullptr, nullptr}};

template <> inline constexpr auto c2py::tp_name<A<3>>       = "bug_tpl_type.A3";
template <> inline constexpr const char *c2py::tp_doc<A<3>> = R"DOC(   )DOC";

static auto init_1                                 = c2py::dispatcher_c_kw_t{c2py::c_constructor<A<3>>()};
template <> constexpr initproc c2py::tp_init<A<3>> = c2py::pyfkw_constructor<init_1>;
// f
static auto const fun_0 =
   c2py::dispatcher_f_kw_t{c2py::cmethod([](A<3> &self, std::vector<std::array<int, 3>> v) { return self.f(v); }, "self", "v")};
static const auto doc_d_0 = fun_0.doc(R"DOC()DOC");

// ----- Method table ----
template <>
PyMethodDef c2py::tp_methods<A<3>>[] = {
   {"f", (PyCFunction)c2py::pyfkw<fun_0>, METH_VARARGS | METH_KEYWORDS, doc_d_0.c_str()},
   {nullptr, nullptr, 0, nullptr} // Sentinel
};

// ----- Method table ----

template <>
constinit PyGetSetDef c2py::tp_getset<A<3>>[] = {

   {nullptr, nullptr, nullptr, nullptr, nullptr}};

template <> inline constexpr auto c2py::tp_name<B<int>>       = "bug_tpl_type.Bi";
template <> inline constexpr const char *c2py::tp_doc<B<int>> = R"DOC(   )DOC";

static auto init_2                                   = c2py::dispatcher_c_kw_t{c2py::c_constructor<B<int>>()};
template <> constexpr initproc c2py::tp_init<B<int>> = c2py::pyfkw_constructor<init_2>;
// f
static auto const fun_1 =
   c2py::dispatcher_f_kw_t{c2py::cmethod([](B<int> &self, std::vector<std::array<int, 3>> v) { return self.f(v); }, "self", "v")};
static const auto doc_d_1 = fun_1.doc(R"DOC()DOC");

// ----- Method table ----
template <>
PyMethodDef c2py::tp_methods<B<int>>[] = {
   {"f", (PyCFunction)c2py::pyfkw<fun_1>, METH_VARARGS | METH_KEYWORDS, doc_d_1.c_str()},
   {nullptr, nullptr, 0, nullptr} // Sentinel
};

// ----- Method table ----

template <>
constinit PyGetSetDef c2py::tp_getset<B<int>>[] = {

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
                                        "bug_tpl_type",    /* name of module */
                                        R"RAWDOC()RAWDOC", /* module documentation, may be NULL */
                                        -1, /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
                                        module_methods,
                                        NULL,
                                        NULL,
                                        NULL,
                                        NULL};

//--------------------- module init function -----------------------------

extern "C" __attribute__((visibility("default"))) PyObject *PyInit_bug_tpl_type() {

  if (not c2py::check_python_version("bug_tpl_type")) return NULL;

  // import numpy iff 'numpy/arrayobject.h' included
#ifdef Py_ARRAYOBJECT_H
  import_array();
#endif

  PyObject *m;

  if (PyType_Ready(&c2py::wrap_pytype<c2py::py_range>) < 0) return NULL;
  if (PyType_Ready(&c2py::wrap_pytype<C>) < 0) return NULL;
  if (PyType_Ready(&c2py::wrap_pytype<A<3>>) < 0) return NULL;
  if (PyType_Ready(&c2py::wrap_pytype<B<int>>) < 0) return NULL;

  m = PyModule_Create(&module_def);
  if (m == NULL) return NULL;

  auto &conv_table = *c2py::conv_table_sptr.get();

  conv_table[std::type_index(typeid(c2py::py_range)).name()] = &c2py::wrap_pytype<c2py::py_range>;
  c2py::add_type_object_to_main<C>("C", m, conv_table);
  c2py::add_type_object_to_main<A<3>>("A3", m, conv_table);
  c2py::add_type_object_to_main<B<int>>("Bi", m, conv_table);

  return m;
}
#endif
// CLAIR_WRAP_GEN


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
#include "issue9.cpp"

using c2py::operator"" _a;

// ==================== Wrapped classes =====================

#ifndef C2PY_HXX_DECLARATION_issue9_GUARDS
#define C2PY_HXX_DECLARATION_issue9_GUARDS
template <> constexpr bool c2py::is_wrapped<dummy_class> = true;
#endif

// ==================== enums =====================

// ==================== module classes =====================

template <> inline const std::string c2py::cpp_name<dummy_class>   = "dummy_class";
template <> inline constexpr auto c2py::tp_name<dummy_class>       = "issue9.DummyClass";
template <> inline constexpr const char *c2py::tp_doc<dummy_class> = R"DOC(   )DOC";

static auto init_0                                        = c2py::dispatcher_c_kw_t{c2py::c_constructor<dummy_class>()};
template <> constexpr initproc c2py::tp_init<dummy_class> = c2py::pyfkw_constructor<init_0>;
// do_thing
static auto const fun_0 =
   c2py::dispatcher_f_kw_t{c2py::cfun(c2py::castm<const std::function<double(const dummy_class::myarray<1> &)> &>(&dummy_class::do_thing), "")};
static const auto doc_d_0 = fun_0.doc({R"DOC(   )DOC"});

// ----- Method table ----
template <>
PyMethodDef c2py::tp_methods<dummy_class>[] = {
   {"do_thing", (PyCFunction)c2py::pyfkw<fun_0>, METH_VARARGS | METH_KEYWORDS, doc_d_0.c_str()},
   {nullptr, nullptr, 0, nullptr} // Sentinel
};

// ----- Method table ----

template <>
constinit PyGetSetDef c2py::tp_getset<dummy_class>[] = {

   {nullptr, nullptr, nullptr, nullptr, nullptr}};

// ==================== module functions ====================

// f
static auto const fun_1 = c2py::dispatcher_f_kw_t{c2py::cfun(c2py::cast<std::array<int, 3>>(&f), "a")};

// g
static auto const fun_2 = c2py::dispatcher_f_kw_t{c2py::cfun(c2py::cast<const std::array<int, 3> &>(&g), "a")};

// h
static auto const fun_3 = c2py::dispatcher_f_kw_t{c2py::cfun(c2py::cast<std::array<int, 3>>(&h), "a")};

static const auto doc_d_1 = fun_1.doc({R"DOC(   )DOC"});
static const auto doc_d_2 = fun_2.doc({R"DOC(   )DOC"});
static const auto doc_d_3 = fun_3.doc({R"DOC(   )DOC"});
//--------------------- module function table  -----------------------------

static PyMethodDef module_methods[] = {
   {"f", (PyCFunction)c2py::pyfkw<fun_1>, METH_VARARGS | METH_KEYWORDS, doc_d_1.c_str()},
   {"g", (PyCFunction)c2py::pyfkw<fun_2>, METH_VARARGS | METH_KEYWORDS, doc_d_2.c_str()},
   {"h", (PyCFunction)c2py::pyfkw<fun_3>, METH_VARARGS | METH_KEYWORDS, doc_d_3.c_str()},
   {nullptr, nullptr, 0, nullptr} // Sentinel
};

//--------------------- module struct & init error definition ------------

//// module doc directly in the code or "" if not present...
/// Or mandatory ?
static struct PyModuleDef module_def = {PyModuleDef_HEAD_INIT,
                                        "issue9",          /* name of module */
                                        R"RAWDOC()RAWDOC", /* module documentation, may be NULL */
                                        -1, /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
                                        module_methods,
                                        NULL,
                                        NULL,
                                        NULL,
                                        NULL};

//--------------------- module init function -----------------------------

extern "C" __attribute__((visibility("default"))) PyObject *PyInit_issue9() {

  if (not c2py::check_python_version()) return NULL;

    // import numpy iff 'numpy/arrayobject.h' included
#ifdef Py_ARRAYOBJECT_H
  import_array();
#endif

  PyObject *m;

  if (PyType_Ready(&c2py::wrap_pytype<c2py::py_range>) < 0) return NULL;
  if (PyType_Ready(&c2py::wrap_pytype<dummy_class>) < 0) return NULL;

  m = PyModule_Create(&module_def);
  if (m == NULL) return NULL;

  auto &conv_table = *c2py::conv_table_sptr.get();

  conv_table[std::type_index(typeid(c2py::py_range)).name()] = &c2py::wrap_pytype<c2py::py_range>;
  CLAIR_C2PY_ADD_TYPE_OBJECT(dummy_class, "DummyClass");

  return m;
}


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

template <> constexpr bool c2py::is_wrapped<a_struct> = true;
template <> constexpr bool c2py::is_wrapped<opaque>   = true;
template <> constexpr bool c2py::is_wrapped<opaque2>  = true;

// ==================== enums =====================

// ==================== module classes =====================

template <> inline constexpr auto c2py::tp_name<a_struct> = "ignore.AStruct";

static int synth_constructor_0(PyObject *self, PyObject *args, PyObject *kwargs) {
  if (args and PyTuple_Check(args) and (PyTuple_Size(args) > 0)) {
    PyErr_SetString(PyExc_RuntimeError, ("Error in constructing a_struct.\nNo positional arguments allowed. Use keywords arguments"));
    return -1;
  }
  c2py::pydict_extractor de{kwargs};
  try {
    ((c2py::wrap<a_struct> *)self)->_c = new a_struct{};
  } catch (std::exception const &e) {
    PyErr_SetString(PyExc_RuntimeError, ("Error in constructing a_struct from a Python dict.\n   "s + e.what()).c_str());
    return -1;
  }
  auto &self_c = *(((c2py::wrap<a_struct> *)self)->_c);
  de("a", self_c.a, false);
  return de.check();
}

template <> constexpr initproc c2py::tp_init<a_struct> = synth_constructor_0;

template <>
const std::string c2py::tp_ctor_doc<a_struct> =
   c2py::replace_tags(R"DOC(Synthesized constructor with the following keyword arguments:

Parameters
----------
a : {par_0}

)DOC",
                      "par", std::vector<std::string>{std::vector<std::string>{c2py::python_typename<int>()}});

// ----- Method table ----
template <>
PyMethodDef c2py::tp_methods<a_struct>[] = {

   {nullptr, nullptr, 0, nullptr} // Sentinel
};

constexpr auto doc_member_0 = R"DOC()DOC";
static PyObject *prop_get_dict_0(PyObject *self, void *) {
  auto &self_c = *(((c2py::wrap<a_struct> *)self)->_c);
  c2py::pydict dic;
  dic["a"] = self_c.a;
  return dic.new_ref();
}

// ----- Method table ----

template <>
constinit PyGetSetDef c2py::tp_getset<a_struct>[] = {c2py::getsetdef_from_member<&a_struct::a, a_struct>("a", doc_member_0),
                                                     {"__dict__", (getter)prop_get_dict_0, nullptr, "", nullptr},
                                                     {nullptr, nullptr, nullptr, nullptr, nullptr}};

template <> const std::string c2py::tp_doc<a_struct>    = R"DOC()DOC" + c2py::tp_ctor_doc<a_struct>;
template <> inline constexpr auto c2py::tp_name<opaque> = "ignore.Opaque";

// ----- Method table ----
template <>
PyMethodDef c2py::tp_methods<opaque>[] = {

   {nullptr, nullptr, 0, nullptr} // Sentinel
};

// ----- Method table ----

template <>
constinit PyGetSetDef c2py::tp_getset<opaque>[] = {

   {nullptr, nullptr, nullptr, nullptr, nullptr}};

template <> const std::string c2py::tp_doc<opaque>       = R"DOC()DOC" + c2py::tp_ctor_doc<opaque>;
template <> inline constexpr auto c2py::tp_name<opaque2> = "ignore.Opaque2";
static auto init_0                                       = c2py::dispatcher_c_kw_t{c2py::c_constructor<opaque2>()};
template <> constexpr initproc c2py::tp_init<opaque2>    = c2py::pyfkw_constructor<init_0>;
template <> const std::string c2py::tp_ctor_doc<opaque2> = init_0.doc(R"DOC()DOC", std::vector<std::string>{}, std::vector<std::string>{});

// ----- Method table ----
template <>
PyMethodDef c2py::tp_methods<opaque2>[] = {

   {nullptr, nullptr, 0, nullptr} // Sentinel
};

// ----- Method table ----

template <>
constinit PyGetSetDef c2py::tp_getset<opaque2>[] = {

   {nullptr, nullptr, nullptr, nullptr, nullptr}};

template <> const std::string c2py::tp_doc<opaque2> = R"DOC()DOC" + c2py::tp_ctor_doc<opaque2>;

// ==================== module functions ====================

// inc_opaque
static auto const fun_0 = c2py::dispatcher_f_kw_t{c2py::cfun([](opaque &w) { return inc_opaque(w); }, "w")};

// inc_opaque2
static auto const fun_1 = c2py::dispatcher_f_kw_t{c2py::cfun([](opaque2 &w) { return inc_opaque2(w); }, "w")};

// make_opaque
static auto const fun_2 = c2py::dispatcher_f_kw_t{c2py::cfun([]() { return make_opaque(); })};

// make_opaque2
static auto const fun_3 = c2py::dispatcher_f_kw_t{c2py::cfun([]() { return make_opaque2(); })};

// take_opaque
static auto const fun_4 = c2py::dispatcher_f_kw_t{c2py::cfun([](const opaque &w) { return take_opaque(w); }, "w")};

// take_opaque2
static auto const fun_5 = c2py::dispatcher_f_kw_t{c2py::cfun([](const opaque2 &w) { return take_opaque2(w); }, "w")};

static const auto doc_d_0 = fun_0.doc(R"DOC()DOC", std::vector<std::string>{}, std::vector<std::string>{});
static const auto doc_d_1 = fun_1.doc(R"DOC()DOC", std::vector<std::string>{}, std::vector<std::string>{});
static const auto doc_d_2 = fun_2.doc(R"DOC()DOC", std::vector<std::string>{}, std::vector<std::string>{});
static const auto doc_d_3 = fun_3.doc(R"DOC()DOC", std::vector<std::string>{}, std::vector<std::string>{});
static const auto doc_d_4 = fun_4.doc(R"DOC()DOC", std::vector<std::string>{}, std::vector<std::string>{});
static const auto doc_d_5 = fun_5.doc(R"DOC()DOC", std::vector<std::string>{}, std::vector<std::string>{});
//--------------------- module function table  -----------------------------

static PyMethodDef module_methods[] = {
   {"inc_opaque", (PyCFunction)c2py::pyfkw<fun_0>, METH_VARARGS | METH_KEYWORDS, doc_d_0.c_str()},
   {"inc_opaque2", (PyCFunction)c2py::pyfkw<fun_1>, METH_VARARGS | METH_KEYWORDS, doc_d_1.c_str()},
   {"make_opaque", (PyCFunction)c2py::pyfkw<fun_2>, METH_VARARGS | METH_KEYWORDS, doc_d_2.c_str()},
   {"make_opaque2", (PyCFunction)c2py::pyfkw<fun_3>, METH_VARARGS | METH_KEYWORDS, doc_d_3.c_str()},
   {"take_opaque", (PyCFunction)c2py::pyfkw<fun_4>, METH_VARARGS | METH_KEYWORDS, doc_d_4.c_str()},
   {"take_opaque2", (PyCFunction)c2py::pyfkw<fun_5>, METH_VARARGS | METH_KEYWORDS, doc_d_5.c_str()},
   {nullptr, nullptr, 0, nullptr} // Sentinel
};

//--------------------- module struct & init error definition ------------

//// module doc directly in the code or "" if not present...
/// Or mandatory ?
static struct PyModuleDef module_def = {PyModuleDef_HEAD_INIT,
                                        "ignore",          /* name of module */
                                        R"RAWDOC()RAWDOC", /* module documentation, may be NULL */
                                        -1, /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
                                        module_methods,
                                        NULL,
                                        NULL,
                                        NULL,
                                        NULL};

//--------------------- module init function -----------------------------

extern "C" __attribute__((visibility("default"))) PyObject *PyInit_ignore() {

  if (not c2py::check_python_version("ignore")) return NULL;

  // import numpy iff 'numpy/arrayobject.h' included
#ifdef Py_ARRAYOBJECT_H
  import_array();
#endif

  PyObject *m;

  if (PyType_Ready(&c2py::wrap_pytype<c2py::py_range>) < 0) return NULL;
  if (PyType_Ready(&c2py::wrap_pytype<a_struct>) < 0) return NULL;
  if (PyType_Ready(&c2py::wrap_pytype<opaque>) < 0) return NULL;
  if (PyType_Ready(&c2py::wrap_pytype<opaque2>) < 0) return NULL;

  m = PyModule_Create(&module_def);
  if (m == NULL) return NULL;

  auto &conv_table = *c2py::conv_table_sptr.get();

  conv_table[std::type_index(typeid(c2py::py_range)).name()] = &c2py::wrap_pytype<c2py::py_range>;
  c2py::add_type_object_to_main<a_struct>("AStruct", m, conv_table);
  c2py::add_type_object_to_main<opaque>("Opaque", m, conv_table);
  c2py::add_type_object_to_main<opaque2>("Opaque2", m, conv_table);

  return m;
}
#endif
// CLAIR_WRAP_GEN

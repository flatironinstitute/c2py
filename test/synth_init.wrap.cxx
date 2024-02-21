
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
#include "synth_init.cpp"

using c2py::operator"" _a;

// ==================== Wrapped classes =====================

#ifndef C2PY_HXX_DECLARATION_synth_init_GUARDS
#define C2PY_HXX_DECLARATION_synth_init_GUARDS
template <> constexpr bool c2py::is_wrapped<N1::A_ndc>      = true;
template <> constexpr bool c2py::is_wrapped<N1::params>     = true;
template <> constexpr bool c2py::is_wrapped<N1::params_ndc> = true;
#endif

// ==================== enums =====================

// ==================== module classes =====================

template <> inline const std::string c2py::cpp_name<N1::A_ndc>   = "N1::A_ndc";
template <> inline constexpr auto c2py::tp_name<N1::A_ndc>       = "synth_init.ANdc";
template <> inline constexpr const char *c2py::tp_doc<N1::A_ndc> = R"DOC(   )DOC";

static auto init_0                                      = c2py::dispatcher_c_kw_t{c2py::c_constructor<N1::A_ndc, int>("i")};
template <> constexpr initproc c2py::tp_init<N1::A_ndc> = c2py::pyfkw_constructor<init_0>;

// ----- Method table ----
template <>
PyMethodDef c2py::tp_methods<N1::A_ndc>[] = {

   {nullptr, nullptr, 0, nullptr} // Sentinel
};

constexpr auto doc_member_0 = R"DOC()DOC";

// ----- Method table ----

template <>
constinit PyGetSetDef c2py::tp_getset<N1::A_ndc>[] = {c2py::getsetdef_from_member<&N1::A_ndc::u, N1::A_ndc>("u", doc_member_0),

                                                      {nullptr, nullptr, nullptr, nullptr, nullptr}};

template <> inline const std::string c2py::cpp_name<N1::params> = "N1::params";
template <> inline constexpr auto c2py::tp_name<N1::params>     = "synth_init.Params";
template <>
inline constexpr const char *c2py::tp_doc<N1::params> = R"DOC(   * i: int
      An int
   
   * v: std::vector<int>
      A vector of int
   
   * x: double = 10
      A double
   
   * w: std::vector<int> = {1, 2, 3})DOC";

static int synth_constructor_0(PyObject *self, PyObject *args, PyObject *kwargs) {
  if (args and PyTuple_Check(args) and (PyTuple_Size(args) > 0)) {
    PyErr_SetString(PyExc_RuntimeError, ("Error in constructing N1::params.\nNo positional arguments allowed. Use keywords arguments"));
    return -1;
  }
  c2py::pydict_extractor de{kwargs};
  try {
    ((c2py::wrap<N1::params> *)self)->_c = new N1::params{};
  } catch (std::exception const &e) {
    PyErr_SetString(PyExc_RuntimeError, ("Error in constructing N1::params from a Python dict.\n   "s + e.what()).c_str());
    return -1;
  }
  auto &self_c = *(((c2py::wrap<N1::params> *)self)->_c);
  de("i", self_c.i, false);
  de("x", self_c.x, true);
  de("v", self_c.v, false);
  de("w", self_c.w, true);
  return de.check();
}

template <> constexpr initproc c2py::tp_init<N1::params> = synth_constructor_0;

// ----- Method table ----
template <>
PyMethodDef c2py::tp_methods<N1::params>[] = {

   {nullptr, nullptr, 0, nullptr} // Sentinel
};

constexpr auto doc_member_1 = R"DOC(/// An int)DOC";
constexpr auto doc_member_2 = R"DOC(/// A double)DOC";
constexpr auto doc_member_3 = R"DOC(/// A vector of int)DOC";
constexpr auto doc_member_4 = R"DOC()DOC";
static PyObject *prop_get_dict_0(PyObject *self, void *) {
  auto &self_c = *(((c2py::wrap<N1::params> *)self)->_c);
  c2py::pydict dic;
  dic["i"] = self_c.i;
  dic["x"] = self_c.x;
  dic["v"] = self_c.v;
  dic["w"] = self_c.w;
  return dic.new_ref();
}

// ----- Method table ----

template <>
constinit PyGetSetDef c2py::tp_getset<N1::params>[] = {c2py::getsetdef_from_member<&N1::params::i, N1::params>("i", doc_member_1),
                                                       c2py::getsetdef_from_member<&N1::params::x, N1::params>("x", doc_member_2),
                                                       c2py::getsetdef_from_member<&N1::params::v, N1::params>("v", doc_member_3),
                                                       c2py::getsetdef_from_member<&N1::params::w, N1::params>("w", doc_member_4),
                                                       {"__dict__", (getter)prop_get_dict_0, nullptr, "", nullptr},
                                                       {nullptr, nullptr, nullptr, nullptr, nullptr}};

template <> inline const std::string c2py::cpp_name<N1::params_ndc> = "N1::params_ndc";
template <> inline constexpr auto c2py::tp_name<N1::params_ndc>     = "synth_init.ParamsNdc";
template <>
inline constexpr const char *c2py::tp_doc<N1::params_ndc> = R"DOC(   * i: int
      An int
   
   * ndc1: N1::A_ndc
      A non default constructible object
   
   * v: std::vector<int>
      A vector of int
   
   * x: double = 10
      A double
      with a long doc
   
   * ndc2: N1::A_ndc = A_ndc{9}
      A non default constructible object with a default init
   
   * w: std::vector<int> = {1, 2, 3})DOC";

static int synth_constructor_1(PyObject *self, PyObject *args, PyObject *kwargs) {
  if (args and PyTuple_Check(args) and (PyTuple_Size(args) > 0)) {
    PyErr_SetString(PyExc_RuntimeError, ("Error in constructing N1::params_ndc.\nNo positional arguments allowed. Use keywords arguments"));
    return -1;
  }
  c2py::pydict_extractor de{kwargs};
  try {
    ((c2py::wrap<N1::params_ndc> *)self)->_c = new N1::params_ndc{.ndc1 = de.get<N1::A_ndc>("ndc1")};
  } catch (std::exception const &e) {
    PyErr_SetString(PyExc_RuntimeError, ("Error in constructing N1::params_ndc from a Python dict.\n   "s + e.what()).c_str());
    return -1;
  }
  auto &self_c = *(((c2py::wrap<N1::params_ndc> *)self)->_c);
  de("i", self_c.i, false);
  de("x", self_c.x, true);
  de("ndc2", self_c.ndc2, true);
  de("v", self_c.v, false);
  de("w", self_c.w, true);
  return de.check();
}

template <> constexpr initproc c2py::tp_init<N1::params_ndc> = synth_constructor_1;

// ----- Method table ----
template <>
PyMethodDef c2py::tp_methods<N1::params_ndc>[] = {

   {nullptr, nullptr, 0, nullptr} // Sentinel
};

constexpr auto doc_member_5  = R"DOC(/// An int)DOC";
constexpr auto doc_member_6  = R"DOC(/// A double
    /// with a long doc)DOC";
constexpr auto doc_member_7  = R"DOC(/// A non default constructible object)DOC";
constexpr auto doc_member_8  = R"DOC(/// A non default constructible object with a default init)DOC";
constexpr auto doc_member_9  = R"DOC(/// A vector of int)DOC";
constexpr auto doc_member_10 = R"DOC()DOC";
static PyObject *prop_get_dict_1(PyObject *self, void *) {
  auto &self_c = *(((c2py::wrap<N1::params_ndc> *)self)->_c);
  c2py::pydict dic;
  dic["i"]    = self_c.i;
  dic["x"]    = self_c.x;
  dic["ndc1"] = self_c.ndc1;
  dic["ndc2"] = self_c.ndc2;
  dic["v"]    = self_c.v;
  dic["w"]    = self_c.w;
  return dic.new_ref();
}

// ----- Method table ----

template <>
constinit PyGetSetDef c2py::tp_getset<N1::params_ndc>[] = {c2py::getsetdef_from_member<&N1::params_ndc::i, N1::params_ndc>("i", doc_member_5),
                                                           c2py::getsetdef_from_member<&N1::params_ndc::x, N1::params_ndc>("x", doc_member_6),
                                                           c2py::getsetdef_from_member<&N1::params_ndc::ndc1, N1::params_ndc>("ndc1", doc_member_7),
                                                           c2py::getsetdef_from_member<&N1::params_ndc::ndc2, N1::params_ndc>("ndc2", doc_member_8),
                                                           c2py::getsetdef_from_member<&N1::params_ndc::v, N1::params_ndc>("v", doc_member_9),
                                                           c2py::getsetdef_from_member<&N1::params_ndc::w, N1::params_ndc>("w", doc_member_10),
                                                           {"__dict__", (getter)prop_get_dict_1, nullptr, "", nullptr},
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
                                        "synth_init",      /* name of module */
                                        R"RAWDOC()RAWDOC", /* module documentation, may be NULL */
                                        -1, /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
                                        module_methods,
                                        NULL,
                                        NULL,
                                        NULL,
                                        NULL};

//--------------------- module init function -----------------------------

extern "C" __attribute__((visibility("default"))) PyObject *PyInit_synth_init() {

  if (not c2py::check_python_version()) return NULL;

    // import numpy iff 'numpy/arrayobject.h' included
#ifdef Py_ARRAYOBJECT_H
  import_array();
#endif

  PyObject *m;

  if (PyType_Ready(&c2py::wrap_pytype<c2py::py_range>) < 0) return NULL;
  if (PyType_Ready(&c2py::wrap_pytype<N1::A_ndc>) < 0) return NULL;
  if (PyType_Ready(&c2py::wrap_pytype<N1::params>) < 0) return NULL;
  if (PyType_Ready(&c2py::wrap_pytype<N1::params_ndc>) < 0) return NULL;

  m = PyModule_Create(&module_def);
  if (m == NULL) return NULL;

  auto &conv_table = *c2py::conv_table_sptr.get();

  conv_table[std::type_index(typeid(c2py::py_range)).name()] = &c2py::wrap_pytype<c2py::py_range>;
  CLAIR_C2PY_ADD_TYPE_OBJECT(N1::A_ndc, "ANdc");
  CLAIR_C2PY_ADD_TYPE_OBJECT(N1::params, "Params");
  CLAIR_C2PY_ADD_TYPE_OBJECT(N1::params_ndc, "ParamsNdc");

  return m;
}

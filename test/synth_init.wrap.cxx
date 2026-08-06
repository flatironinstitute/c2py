
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

// --------- class _c2py_cls_40e5fc76 -----------
using _c2py_cls_40e5fc76                                            = N1::no_defaults;
template <> constexpr bool c2py::is_wrapped<_c2py_cls_40e5fc76>     = true;
template <> inline constexpr auto c2py::tp_name<_c2py_cls_40e5fc76> = "synth_init.NoDefaults";

static int synth_constructor_7e508fc8(PyObject *self, PyObject *args, PyObject *kwargs) {
  if (args and PyTuple_Check(args) and (PyTuple_Size(args) > 0)) {
    PyErr_SetString(PyExc_RuntimeError, ("Error in constructing N1::no_defaults.\nNo positional arguments allowed. Use keywords arguments"));
    return -1;
  }
  c2py::pydict_extractor de{kwargs};
  try {
    ((c2py::wrap<_c2py_cls_40e5fc76> *)self)->_c = new _c2py_cls_40e5fc76{};
  } catch (std::exception const &e) {
    PyErr_SetString(PyExc_RuntimeError, ("Error in constructing N1::no_defaults from a Python dict.\n   "s + e.what()).c_str());
    return -1;
  }
  auto &self_c = *(((c2py::wrap<_c2py_cls_40e5fc76> *)self)->_c);
  de("a", self_c.a, false);
  return de.check();
}

template <> constexpr initproc c2py::tp_init<_c2py_cls_40e5fc76> = synth_constructor_7e508fc8;

template <>
const std::string c2py::tp_ctor_doc<_c2py_cls_40e5fc76> = c2py::replace_tags(R"DOC(Synthesized constructor with the following keyword arguments:

Parameters
----------
a : {par_0}

)DOC",
                                                                             "par", {c2py::python_typename<int>()});

// ----- Method table ----
// clang-format off
template <> PyMethodDef c2py::tp_methods<_c2py_cls_40e5fc76>[] = {
   {nullptr, nullptr, 0, nullptr} // Sentinel
};
// clang-format on

constexpr auto _c2py_doc_member_240363c1 = R"DOC()DOC";
static PyObject *prop_get_dict_7e508fc8(PyObject *self, void *) {
  auto &self_c = *(((c2py::wrap<_c2py_cls_40e5fc76> *)self)->_c);
  c2py::pydict dic;
  dic["a"] = self_c.a;
  return dic.new_ref();
}

// ----- Member and property table ----

template <>
constinit PyGetSetDef c2py::tp_getset<_c2py_cls_40e5fc76>[] = {
   c2py::getsetdef_from_member<&_c2py_cls_40e5fc76::a, _c2py_cls_40e5fc76>("a", _c2py_doc_member_240363c1),
   {"__dict__", (getter)prop_get_dict_7e508fc8, nullptr, "", nullptr},
   {nullptr, nullptr, nullptr, nullptr, nullptr}};

template <> const std::string c2py::tp_doc<_c2py_cls_40e5fc76> = R"DOC()DOC" + c2py::tp_ctor_doc<_c2py_cls_40e5fc76>;
// --------- class _c2py_cls_23873e83 -----------
using _c2py_cls_23873e83                                            = N1::with_defaults;
template <> constexpr bool c2py::is_wrapped<_c2py_cls_23873e83>     = true;
template <> inline constexpr auto c2py::tp_name<_c2py_cls_23873e83> = "synth_init.WithDefaults";

static int synth_constructor_0ff67923(PyObject *self, PyObject *args, PyObject *kwargs) {
  if (args and PyTuple_Check(args) and (PyTuple_Size(args) > 0)) {
    PyErr_SetString(PyExc_RuntimeError, ("Error in constructing N1::with_defaults.\nNo positional arguments allowed. Use keywords arguments"));
    return -1;
  }
  c2py::pydict_extractor de{kwargs};
  try {
    ((c2py::wrap<_c2py_cls_23873e83> *)self)->_c = new _c2py_cls_23873e83{};
  } catch (std::exception const &e) {
    PyErr_SetString(PyExc_RuntimeError, ("Error in constructing N1::with_defaults from a Python dict.\n   "s + e.what()).c_str());
    return -1;
  }
  auto &self_c = *(((c2py::wrap<_c2py_cls_23873e83> *)self)->_c);
  de("a", self_c.a, true);
  return de.check();
}

template <> constexpr initproc c2py::tp_init<_c2py_cls_23873e83> = synth_constructor_0ff67923;

template <>
const std::string c2py::tp_ctor_doc<_c2py_cls_23873e83> = c2py::replace_tags(R"DOC(Synthesized constructor with the following keyword arguments:

Parameters
----------
a : {par_0}, default=5

)DOC",
                                                                             "par", {c2py::python_typename<int>()});

// ----- Method table ----
// clang-format off
template <> PyMethodDef c2py::tp_methods<_c2py_cls_23873e83>[] = {
   {nullptr, nullptr, 0, nullptr} // Sentinel
};
// clang-format on

constexpr auto _c2py_doc_member_e42194f6 = R"DOC()DOC";
static PyObject *prop_get_dict_0ff67923(PyObject *self, void *) {
  auto &self_c = *(((c2py::wrap<_c2py_cls_23873e83> *)self)->_c);
  c2py::pydict dic;
  dic["a"] = self_c.a;
  return dic.new_ref();
}

// ----- Member and property table ----

template <>
constinit PyGetSetDef c2py::tp_getset<_c2py_cls_23873e83>[] = {
   c2py::getsetdef_from_member<&_c2py_cls_23873e83::a, _c2py_cls_23873e83>("a", _c2py_doc_member_e42194f6),
   {"__dict__", (getter)prop_get_dict_0ff67923, nullptr, "", nullptr},
   {nullptr, nullptr, nullptr, nullptr, nullptr}};

template <> const std::string c2py::tp_doc<_c2py_cls_23873e83> = R"DOC()DOC" + c2py::tp_ctor_doc<_c2py_cls_23873e83>;
// --------- class _c2py_cls_f0d40733 -----------
using _c2py_cls_f0d40733                                            = N1::A_ndc;
template <> constexpr bool c2py::is_wrapped<_c2py_cls_f0d40733>     = true;
template <> inline constexpr auto c2py::tp_name<_c2py_cls_f0d40733> = "synth_init.ANdc";
static const auto _c2py_init_edefc3b5                               = c2py::dispatcher_c_kw_t{c2py::c_constructor<_c2py_cls_f0d40733, int>("i")};
template <> constexpr initproc c2py::tp_init<_c2py_cls_f0d40733>    = c2py::pyfkw_constructor<_c2py_init_edefc3b5>;
template <> const std::string c2py::tp_ctor_doc<_c2py_cls_f0d40733> = _c2py_init_edefc3b5.doc(R"DOC()DOC");

// ----- Method table ----
// clang-format off
template <> PyMethodDef c2py::tp_methods<_c2py_cls_f0d40733>[] = {
   {nullptr, nullptr, 0, nullptr} // Sentinel
};
// clang-format on

constexpr auto _c2py_doc_member_65ded782 = R"DOC()DOC";

// ----- Member and property table ----

template <>
constinit PyGetSetDef c2py::tp_getset<_c2py_cls_f0d40733>[] = {
   c2py::getsetdef_from_member<&_c2py_cls_f0d40733::u, _c2py_cls_f0d40733>("u", _c2py_doc_member_65ded782),

   {nullptr, nullptr, nullptr, nullptr, nullptr}};

template <> const std::string c2py::tp_doc<_c2py_cls_f0d40733> = R"DOC()DOC" + c2py::tp_ctor_doc<_c2py_cls_f0d40733>;
// --------- class _c2py_cls_08b1d68a -----------
using _c2py_cls_08b1d68a                                            = N1::params;
template <> constexpr bool c2py::is_wrapped<_c2py_cls_08b1d68a>     = true;
template <> inline constexpr auto c2py::tp_name<_c2py_cls_08b1d68a> = "synth_init.Params";

static int synth_constructor_5d69d204(PyObject *self, PyObject *args, PyObject *kwargs) {
  if (args and PyTuple_Check(args) and (PyTuple_Size(args) > 0)) {
    PyErr_SetString(PyExc_RuntimeError, ("Error in constructing N1::params.\nNo positional arguments allowed. Use keywords arguments"));
    return -1;
  }
  c2py::pydict_extractor de{kwargs};
  try {
    ((c2py::wrap<_c2py_cls_08b1d68a> *)self)->_c = new _c2py_cls_08b1d68a{};
  } catch (std::exception const &e) {
    PyErr_SetString(PyExc_RuntimeError, ("Error in constructing N1::params from a Python dict.\n   "s + e.what()).c_str());
    return -1;
  }
  auto &self_c = *(((c2py::wrap<_c2py_cls_08b1d68a> *)self)->_c);
  de("i", self_c.i, false);
  de("x", self_c.x, true);
  de("v", self_c.v, false);
  de("w", self_c.w, true);
  return de.check();
}

template <> constexpr initproc c2py::tp_init<_c2py_cls_08b1d68a> = synth_constructor_5d69d204;

template <>
const std::string c2py::tp_ctor_doc<_c2py_cls_08b1d68a> =
   c2py::replace_tags(R"DOC(Synthesized constructor with the following keyword arguments:

Parameters
----------
i : {par_0}

v : {par_1}

x : {par_2}, default=10

w : {par_3}, default={1, 2, 3}

)DOC",
                      "par",
                      {c2py::python_typename<int>(), c2py::python_typename<std::vector<int>>(), c2py::python_typename<double>(),
                       c2py::python_typename<std::vector<int>>()});

// ----- Method table ----
// clang-format off
template <> PyMethodDef c2py::tp_methods<_c2py_cls_08b1d68a>[] = {
   {nullptr, nullptr, 0, nullptr} // Sentinel
};
// clang-format on

constexpr auto _c2py_doc_member_9c97f055 = R"DOC(An int)DOC";
constexpr auto _c2py_doc_member_8b97d592 = R"DOC(A double)DOC";
constexpr auto _c2py_doc_member_8d97d8b8 = R"DOC(A vector of int)DOC";
constexpr auto _c2py_doc_member_8e97da4b = R"DOC()DOC";
static PyObject *prop_get_dict_5d69d204(PyObject *self, void *) {
  auto &self_c = *(((c2py::wrap<_c2py_cls_08b1d68a> *)self)->_c);
  c2py::pydict dic;
  dic["i"] = self_c.i;
  dic["x"] = self_c.x;
  dic["v"] = self_c.v;
  dic["w"] = self_c.w;
  return dic.new_ref();
}

// ----- Member and property table ----

template <>
constinit PyGetSetDef c2py::tp_getset<_c2py_cls_08b1d68a>[] = {
   c2py::getsetdef_from_member<&_c2py_cls_08b1d68a::i, _c2py_cls_08b1d68a>("i", _c2py_doc_member_9c97f055),
   c2py::getsetdef_from_member<&_c2py_cls_08b1d68a::x, _c2py_cls_08b1d68a>("x", _c2py_doc_member_8b97d592),
   c2py::getsetdef_from_member<&_c2py_cls_08b1d68a::v, _c2py_cls_08b1d68a>("v", _c2py_doc_member_8d97d8b8),
   c2py::getsetdef_from_member<&_c2py_cls_08b1d68a::w, _c2py_cls_08b1d68a>("w", _c2py_doc_member_8e97da4b),
   {"__dict__", (getter)prop_get_dict_5d69d204, nullptr, "", nullptr},
   {nullptr, nullptr, nullptr, nullptr, nullptr}};

template <> const std::string c2py::tp_doc<_c2py_cls_08b1d68a> = R"DOC()DOC" + c2py::tp_ctor_doc<_c2py_cls_08b1d68a>;
// --------- class _c2py_cls_fef1ade2 -----------
using _c2py_cls_fef1ade2                                            = N1::params_ndc;
template <> constexpr bool c2py::is_wrapped<_c2py_cls_fef1ade2>     = true;
template <> inline constexpr auto c2py::tp_name<_c2py_cls_fef1ade2> = "synth_init.ParamsNdc";

static int synth_constructor_9416f20e(PyObject *self, PyObject *args, PyObject *kwargs) {
  if (args and PyTuple_Check(args) and (PyTuple_Size(args) > 0)) {
    PyErr_SetString(PyExc_RuntimeError, ("Error in constructing N1::params_ndc.\nNo positional arguments allowed. Use keywords arguments"));
    return -1;
  }
  c2py::pydict_extractor de{kwargs};
  try {
    ((c2py::wrap<_c2py_cls_fef1ade2> *)self)->_c = new _c2py_cls_fef1ade2{.ndc1 = de.get<N1::A_ndc>("ndc1")};
  } catch (std::exception const &e) {
    PyErr_SetString(PyExc_RuntimeError, ("Error in constructing N1::params_ndc from a Python dict.\n   "s + e.what()).c_str());
    return -1;
  }
  auto &self_c = *(((c2py::wrap<_c2py_cls_fef1ade2> *)self)->_c);
  de("i", self_c.i, false);
  de("x", self_c.x, true);
  de("ndc2", self_c.ndc2, true);
  de("v", self_c.v, false);
  de("w", self_c.w, true);
  return de.check();
}

template <> constexpr initproc c2py::tp_init<_c2py_cls_fef1ade2> = synth_constructor_9416f20e;

template <>
const std::string c2py::tp_ctor_doc<_c2py_cls_fef1ade2> =
   c2py::replace_tags(R"DOC(Synthesized constructor with the following keyword arguments:

Parameters
----------
i : {par_0}

ndc1 : {par_1}

v : {par_2}

x : {par_3}, default=10

ndc2 : {par_4}, default=A_ndc{9}

w : {par_5}, default={1, 2, 3}

)DOC",
                      "par",
                      {c2py::python_typename<int>(), c2py::python_typename<N1::A_ndc>(), c2py::python_typename<std::vector<int>>(),
                       c2py::python_typename<double>(), c2py::python_typename<N1::A_ndc>(), c2py::python_typename<std::vector<int>>()});

// ----- Method table ----
// clang-format off
template <> PyMethodDef c2py::tp_methods<_c2py_cls_fef1ade2>[] = {
   {nullptr, nullptr, 0, nullptr} // Sentinel
};
// clang-format on

constexpr auto _c2py_doc_member_92d44c0d = R"DOC(An int)DOC";
constexpr auto _c2py_doc_member_81d4314a = R"DOC(A double
with a long doc)DOC";
constexpr auto _c2py_doc_member_f1eaea7c = R"DOC(A non default constructible object)DOC";
constexpr auto _c2py_doc_member_f4eaef35 = R"DOC(A non default constructible object with a default init)DOC";
constexpr auto _c2py_doc_member_73d41b40 = R"DOC(A vector of int)DOC";
constexpr auto _c2py_doc_member_74d41cd3 = R"DOC()DOC";
static PyObject *prop_get_dict_9416f20e(PyObject *self, void *) {
  auto &self_c = *(((c2py::wrap<_c2py_cls_fef1ade2> *)self)->_c);
  c2py::pydict dic;
  dic["i"]    = self_c.i;
  dic["x"]    = self_c.x;
  dic["ndc1"] = self_c.ndc1;
  dic["ndc2"] = self_c.ndc2;
  dic["v"]    = self_c.v;
  dic["w"]    = self_c.w;
  return dic.new_ref();
}

// ----- Member and property table ----

template <>
constinit PyGetSetDef c2py::tp_getset<_c2py_cls_fef1ade2>[] = {
   c2py::getsetdef_from_member<&_c2py_cls_fef1ade2::i, _c2py_cls_fef1ade2>("i", _c2py_doc_member_92d44c0d),
   c2py::getsetdef_from_member<&_c2py_cls_fef1ade2::x, _c2py_cls_fef1ade2>("x", _c2py_doc_member_81d4314a),
   c2py::getsetdef_from_member<&_c2py_cls_fef1ade2::ndc1, _c2py_cls_fef1ade2>("ndc1", _c2py_doc_member_f1eaea7c),
   c2py::getsetdef_from_member<&_c2py_cls_fef1ade2::ndc2, _c2py_cls_fef1ade2>("ndc2", _c2py_doc_member_f4eaef35),
   c2py::getsetdef_from_member<&_c2py_cls_fef1ade2::v, _c2py_cls_fef1ade2>("v", _c2py_doc_member_73d41b40),
   c2py::getsetdef_from_member<&_c2py_cls_fef1ade2::w, _c2py_cls_fef1ade2>("w", _c2py_doc_member_74d41cd3),
   {"__dict__", (getter)prop_get_dict_9416f20e, nullptr, "", nullptr},
   {nullptr, nullptr, nullptr, nullptr, nullptr}};

template <> const std::string c2py::tp_doc<_c2py_cls_fef1ade2> = R"DOC()DOC" + c2py::tp_ctor_doc<_c2py_cls_fef1ade2>;
// --------- class _c2py_cls_78cab850 -----------
using _c2py_cls_78cab850                                            = N1::tpl_params_ndc<int>;
template <> constexpr bool c2py::is_wrapped<_c2py_cls_78cab850>     = true;
template <> inline constexpr auto c2py::tp_name<_c2py_cls_78cab850> = "synth_init.TplParamNdcInt";

static int synth_constructor_89de09c0(PyObject *self, PyObject *args, PyObject *kwargs) {
  if (args and PyTuple_Check(args) and (PyTuple_Size(args) > 0)) {
    PyErr_SetString(PyExc_RuntimeError, ("Error in constructing N1::tpl_params_ndc<int>.\nNo positional arguments allowed. Use keywords arguments"));
    return -1;
  }
  c2py::pydict_extractor de{kwargs};
  try {
    ((c2py::wrap<_c2py_cls_78cab850> *)self)->_c = new _c2py_cls_78cab850{.ndc1 = de.get<N1::A_ndc>("ndc1")};
  } catch (std::exception const &e) {
    PyErr_SetString(PyExc_RuntimeError, ("Error in constructing N1::tpl_params_ndc<int> from a Python dict.\n   "s + e.what()).c_str());
    return -1;
  }
  auto &self_c = *(((c2py::wrap<_c2py_cls_78cab850> *)self)->_c);
  de("i", self_c.i, false);
  de("x", self_c.x, true);
  de("ndc2", self_c.ndc2, true);
  de("v", self_c.v, false);
  de("w", self_c.w, true);
  return de.check();
}

template <> constexpr initproc c2py::tp_init<_c2py_cls_78cab850> = synth_constructor_89de09c0;

template <>
const std::string c2py::tp_ctor_doc<_c2py_cls_78cab850> =
   c2py::replace_tags(R"DOC(Synthesized constructor with the following keyword arguments:

Parameters
----------
i : {par_0}

x : {par_1}

ndc1 : {par_2}

ndc2 : {par_3}

v : {par_4}

w : {par_5}

)DOC",
                      "par",
                      {c2py::python_typename<int>(), c2py::python_typename<double>(), c2py::python_typename<N1::A_ndc>(),
                       c2py::python_typename<N1::A_ndc>(), c2py::python_typename<std::vector<int>>(), c2py::python_typename<std::vector<int>>()});

// ----- Method table ----
// clang-format off
template <> PyMethodDef c2py::tp_methods<_c2py_cls_78cab850>[] = {
   {nullptr, nullptr, 0, nullptr} // Sentinel
};
// clang-format on

constexpr auto _c2py_doc_member_faa0615f = R"DOC(An int)DOC";
constexpr auto _c2py_doc_member_09a078fc = R"DOC(A double
with a long doc)DOC";
constexpr auto _c2py_doc_member_a73288aa = R"DOC(A non default constructible object)DOC";
constexpr auto _c2py_doc_member_a6328717 = R"DOC(A non default constructible object with a default init)DOC";
constexpr auto _c2py_doc_member_0fa0826e = R"DOC(A vector of int)DOC";
constexpr auto _c2py_doc_member_10a08401 = R"DOC()DOC";
static PyObject *prop_get_dict_89de09c0(PyObject *self, void *) {
  auto &self_c = *(((c2py::wrap<_c2py_cls_78cab850> *)self)->_c);
  c2py::pydict dic;
  dic["i"]    = self_c.i;
  dic["x"]    = self_c.x;
  dic["ndc1"] = self_c.ndc1;
  dic["ndc2"] = self_c.ndc2;
  dic["v"]    = self_c.v;
  dic["w"]    = self_c.w;
  return dic.new_ref();
}

// ----- Member and property table ----

template <>
constinit PyGetSetDef c2py::tp_getset<_c2py_cls_78cab850>[] = {
   c2py::getsetdef_from_member<&_c2py_cls_78cab850::i, _c2py_cls_78cab850>("i", _c2py_doc_member_faa0615f),
   c2py::getsetdef_from_member<&_c2py_cls_78cab850::x, _c2py_cls_78cab850>("x", _c2py_doc_member_09a078fc),
   c2py::getsetdef_from_member<&_c2py_cls_78cab850::ndc1, _c2py_cls_78cab850>("ndc1", _c2py_doc_member_a73288aa),
   c2py::getsetdef_from_member<&_c2py_cls_78cab850::ndc2, _c2py_cls_78cab850>("ndc2", _c2py_doc_member_a6328717),
   c2py::getsetdef_from_member<&_c2py_cls_78cab850::v, _c2py_cls_78cab850>("v", _c2py_doc_member_0fa0826e),
   c2py::getsetdef_from_member<&_c2py_cls_78cab850::w, _c2py_cls_78cab850>("w", _c2py_doc_member_10a08401),
   {"__dict__", (getter)prop_get_dict_89de09c0, nullptr, "", nullptr},
   {nullptr, nullptr, nullptr, nullptr, nullptr}};

template <> const std::string c2py::tp_doc<_c2py_cls_78cab850> = R"DOC()DOC" + c2py::tp_ctor_doc<_c2py_cls_78cab850>;

// ==================== module functions ====================

//--------------------- module function table  -----------------------------

// clang-format off
static PyMethodDef module_methods[] = {
   {nullptr, nullptr, 0, nullptr}  // Sentinel
};
// clang-format on

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

  if (not c2py::check_python_version("synth_init")) return NULL;

  // import numpy iff 'numpy/arrayobject.h' included
#ifdef Py_ARRAYOBJECT_H
  import_array();
#endif

  PyObject *m;

  if (PyType_Ready(&c2py::wrap_pytype<_c2py_cls_40e5fc76>) < 0) return NULL;
  if (PyType_Ready(&c2py::wrap_pytype<_c2py_cls_23873e83>) < 0) return NULL;
  if (PyType_Ready(&c2py::wrap_pytype<_c2py_cls_f0d40733>) < 0) return NULL;
  if (PyType_Ready(&c2py::wrap_pytype<_c2py_cls_08b1d68a>) < 0) return NULL;
  if (PyType_Ready(&c2py::wrap_pytype<_c2py_cls_fef1ade2>) < 0) return NULL;
  if (PyType_Ready(&c2py::wrap_pytype<_c2py_cls_78cab850>) < 0) return NULL;

  m = PyModule_Create(&module_def);
  if (m == NULL) return NULL;

  if (not c2py::register_internal_types()) return NULL;
#define _add_type(T, N)                                                                                                                              \
  if (not c2py::add_type_object_to_main<T>(N, m)) return NULL
  _add_type(_c2py_cls_40e5fc76, "NoDefaults");
  _add_type(_c2py_cls_23873e83, "WithDefaults");
  _add_type(_c2py_cls_f0d40733, "ANdc");
  _add_type(_c2py_cls_08b1d68a, "Params");
  _add_type(_c2py_cls_fef1ade2, "ParamsNdc");
  _add_type(_c2py_cls_78cab850, "TplParamNdcInt");
#undef _add_type

  return m;
}
#endif
// CLAIR_WRAP_GEN

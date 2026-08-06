
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

// --------- class _c2py_cls_c40bf6cc -----------
using _c2py_cls_c40bf6cc                                            = A;
template <> constexpr bool c2py::is_wrapped<_c2py_cls_c40bf6cc>     = true;
template <> inline constexpr auto c2py::tp_name<_c2py_cls_c40bf6cc> = "properties.A";

static int synth_constructor_185b847b(PyObject *self, PyObject *args, PyObject *kwargs) {
  if (args and PyTuple_Check(args) and (PyTuple_Size(args) > 0)) {
    PyErr_SetString(PyExc_RuntimeError, ("Error in constructing A.\nNo positional arguments allowed. Use keywords arguments"));
    return -1;
  }
  c2py::pydict_extractor de{kwargs};
  try {
    ((c2py::wrap<_c2py_cls_c40bf6cc> *)self)->_c = new _c2py_cls_c40bf6cc{};
  } catch (std::exception const &e) {
    PyErr_SetString(PyExc_RuntimeError, ("Error in constructing A from a Python dict.\n   "s + e.what()).c_str());
    return -1;
  }
  auto &self_c = *(((c2py::wrap<_c2py_cls_c40bf6cc> *)self)->_c);
  de("x_", self_c.x_, true);
  de("y_", self_c.y_, true);
  return de.check();
}

template <> constexpr initproc c2py::tp_init<_c2py_cls_c40bf6cc> = synth_constructor_185b847b;

template <>
const std::string c2py::tp_ctor_doc<_c2py_cls_c40bf6cc> = c2py::replace_tags(R"DOC(Synthesized constructor with the following keyword arguments:

Parameters
----------
x_ : {par_0}, default=10

y_ : {par_1}, default=3.14

)DOC",
                                                                             "par", {c2py::python_typename<int>(), c2py::python_typename<double>()});

// ----- Method table ----
// clang-format off
template <> PyMethodDef c2py::tp_methods<_c2py_cls_c40bf6cc>[] = {
   {nullptr, nullptr, 0, nullptr} // Sentinel
};
// clang-format on

constexpr auto _c2py_doc_member_bbaa113d = R"DOC()DOC";
constexpr auto _c2py_doc_member_7babeb14 = R"DOC()DOC";
static PyObject *prop_get_dict_185b847b(PyObject *self, void *) {
  auto &self_c = *(((c2py::wrap<_c2py_cls_c40bf6cc> *)self)->_c);
  c2py::pydict dic;
  dic["x_"] = self_c.x_;
  dic["y_"] = self_c.y_;
  return dic.new_ref();
}
static constexpr auto prop_doc_eeb8a3b0 = R"DOC()DOC";
static constexpr auto prop_doc_efb8a543 = R"DOC()DOC";
static constexpr auto prop_doc_f0b8a6d6 = R"DOC()DOC";

// ----- Member and property table ----

template <>
constinit PyGetSetDef c2py::tp_getset<_c2py_cls_c40bf6cc>[] = {
   c2py::getsetdef_from_member<&_c2py_cls_c40bf6cc::x_, _c2py_cls_c40bf6cc>("x_", _c2py_doc_member_bbaa113d),
   c2py::getsetdef_from_member<&_c2py_cls_c40bf6cc::y_, _c2py_cls_c40bf6cc>("y_", _c2py_doc_member_7babeb14),
   {"x", c2py::getter_from_method<c2py::castmc<>(&A::get_x)>, nullptr, prop_doc_eeb8a3b0, nullptr},
   {"y", c2py::getter_from_method<c2py::castmc<>(&A::get_y)>, (setter)c2py::setter_from_method<&A::set_y>, prop_doc_efb8a543,
    (void *)"Cannot delete the attribute y"},
   {"z", c2py::getter_from_method<c2py::castmc<>(&A::get_z)>, nullptr, prop_doc_f0b8a6d6, nullptr},
   {"__dict__", (getter)prop_get_dict_185b847b, nullptr, "", nullptr},
   {nullptr, nullptr, nullptr, nullptr, nullptr}};

template <> const std::string c2py::tp_doc<_c2py_cls_c40bf6cc> = R"DOC()DOC" + c2py::tp_ctor_doc<_c2py_cls_c40bf6cc>;
// --------- class _c2py_cls_c70bfb85 -----------
using _c2py_cls_c70bfb85                                            = B;
template <> constexpr bool c2py::is_wrapped<_c2py_cls_c70bfb85>     = true;
template <> inline constexpr auto c2py::tp_name<_c2py_cls_c70bfb85> = "properties.B";

static int synth_constructor_4ca6916b(PyObject *self, PyObject *args, PyObject *kwargs) {
  if (args and PyTuple_Check(args) and (PyTuple_Size(args) > 0)) {
    PyErr_SetString(PyExc_RuntimeError, ("Error in constructing B.\nNo positional arguments allowed. Use keywords arguments"));
    return -1;
  }
  c2py::pydict_extractor de{kwargs};
  try {
    ((c2py::wrap<_c2py_cls_c70bfb85> *)self)->_c = new _c2py_cls_c70bfb85{};
  } catch (std::exception const &e) {
    PyErr_SetString(PyExc_RuntimeError, ("Error in constructing B from a Python dict.\n   "s + e.what()).c_str());
    return -1;
  }
  auto &self_c = *(((c2py::wrap<_c2py_cls_c70bfb85> *)self)->_c);
  de("val_", self_c.val_, true);
  return de.check();
}

template <> constexpr initproc c2py::tp_init<_c2py_cls_c70bfb85> = synth_constructor_4ca6916b;

template <>
const std::string c2py::tp_ctor_doc<_c2py_cls_c70bfb85> = c2py::replace_tags(R"DOC(Synthesized constructor with the following keyword arguments:

Parameters
----------
val_ : {par_0}, default=7

)DOC",
                                                                             "par", {c2py::python_typename<int>()});

// ----- Method table ----
// clang-format off
template <> PyMethodDef c2py::tp_methods<_c2py_cls_c70bfb85>[] = {
   {nullptr, nullptr, 0, nullptr} // Sentinel
};
// clang-format on

constexpr auto _c2py_doc_member_2e40b789 = R"DOC()DOC";
static PyObject *prop_get_dict_4ca6916b(PyObject *self, void *) {
  auto &self_c = *(((c2py::wrap<_c2py_cls_c70bfb85> *)self)->_c);
  c2py::pydict dic;
  dic["val_"] = self_c.val_;
  return dic.new_ref();
}
static constexpr auto prop_doc_f0775252 = R"DOC()DOC";
static constexpr auto prop_doc_666b83ac = R"DOC()DOC";

// ----- Member and property table ----

template <>
constinit PyGetSetDef c2py::tp_getset<_c2py_cls_c70bfb85>[] = {
   c2py::getsetdef_from_member<&_c2py_cls_c70bfb85::val_, _c2py_cls_c70bfb85>("val_", _c2py_doc_member_2e40b789),
   {"dval", c2py::getter_from_fun<&b_get_dval>, (setter)c2py::setter_from_fun<&b_set_dval>, prop_doc_f0775252,
    (void *)"Cannot delete the attribute dval"},
   {"val", c2py::getter_from_fun<&b_get_val>, nullptr, prop_doc_666b83ac, nullptr},
   {"__dict__", (getter)prop_get_dict_4ca6916b, nullptr, "", nullptr},
   {nullptr, nullptr, nullptr, nullptr, nullptr}};

template <> const std::string c2py::tp_doc<_c2py_cls_c70bfb85> = R"DOC()DOC" + c2py::tp_ctor_doc<_c2py_cls_c70bfb85>;
// --------- class _c2py_cls_c60bf9f2 -----------
using _c2py_cls_c60bf9f2                                            = C;
template <> constexpr bool c2py::is_wrapped<_c2py_cls_c60bf9f2>     = true;
template <> inline constexpr auto c2py::tp_name<_c2py_cls_c60bf9f2> = "properties.C";

static int synth_constructor_12b36bc6(PyObject *self, PyObject *args, PyObject *kwargs) {
  if (args and PyTuple_Check(args) and (PyTuple_Size(args) > 0)) {
    PyErr_SetString(PyExc_RuntimeError, ("Error in constructing C.\nNo positional arguments allowed. Use keywords arguments"));
    return -1;
  }
  c2py::pydict_extractor de{kwargs};
  try {
    ((c2py::wrap<_c2py_cls_c60bf9f2> *)self)->_c = new _c2py_cls_c60bf9f2{};
  } catch (std::exception const &e) {
    PyErr_SetString(PyExc_RuntimeError, ("Error in constructing C from a Python dict.\n   "s + e.what()).c_str());
    return -1;
  }
  auto &self_c = *(((c2py::wrap<_c2py_cls_c60bf9f2> *)self)->_c);
  de("v_", self_c.v_, true);
  return de.check();
}

template <> constexpr initproc c2py::tp_init<_c2py_cls_c60bf9f2> = synth_constructor_12b36bc6;

template <>
const std::string c2py::tp_ctor_doc<_c2py_cls_c60bf9f2> = c2py::replace_tags(R"DOC(Synthesized constructor with the following keyword arguments:

Parameters
----------
v_ : {par_0}, default=42

)DOC",
                                                                             "par", {c2py::python_typename<int>()});
// add
static auto const _c2py_fun_ddb14855 =
   c2py::dispatcher_f_kw_t{c2py::cmethod([](_c2py_cls_c60bf9f2 const &self, int n) -> decltype(auto) { return self.add(n); }, "self", "n")};

static const auto _c2py_doc_ddb14855 = _c2py_fun_ddb14855.doc(R"DOC()DOC");

// ----- Method table ----
// clang-format off
template <> PyMethodDef c2py::tp_methods<_c2py_cls_c60bf9f2>[] = {
   PMDF("add", ddb14855),
   {nullptr, nullptr, 0, nullptr} // Sentinel
};
// clang-format on

constexpr auto _c2py_doc_member_f770ad5d = R"DOC()DOC";
static PyObject *prop_get_dict_12b36bc6(PyObject *self, void *) {
  auto &self_c = *(((c2py::wrap<_c2py_cls_c60bf9f2> *)self)->_c);
  c2py::pydict dic;
  dic["v_"] = self_c.v_;
  return dic.new_ref();
}
static constexpr auto prop_doc_d8b073e7 = R"DOC()DOC";

// ----- Member and property table ----

template <>
constinit PyGetSetDef c2py::tp_getset<_c2py_cls_c60bf9f2>[] = {
   c2py::getsetdef_from_member<&_c2py_cls_c60bf9f2::v_, _c2py_cls_c60bf9f2>("v_", _c2py_doc_member_f770ad5d),
   {"value", c2py::getter_from_method<c2py::castmc<>(&C::value)>, nullptr, prop_doc_d8b073e7, nullptr},
   {"__dict__", (getter)prop_get_dict_12b36bc6, nullptr, "", nullptr},
   {nullptr, nullptr, nullptr, nullptr, nullptr}};

template <> const std::string c2py::tp_doc<_c2py_cls_c60bf9f2> = R"DOC()DOC" + c2py::tp_ctor_doc<_c2py_cls_c60bf9f2>;

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
                                        "properties",      /* name of module */
                                        R"RAWDOC()RAWDOC", /* module documentation, may be NULL */
                                        -1, /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
                                        module_methods,
                                        NULL,
                                        NULL,
                                        NULL,
                                        NULL};

//--------------------- module init function -----------------------------

extern "C" __attribute__((visibility("default"))) PyObject *PyInit_properties() {

  if (not c2py::check_python_version("properties")) return NULL;

  // import numpy iff 'numpy/arrayobject.h' included
#ifdef Py_ARRAYOBJECT_H
  import_array();
#endif

  PyObject *m;

  if (PyType_Ready(&c2py::wrap_pytype<_c2py_cls_c40bf6cc>) < 0) return NULL;
  if (PyType_Ready(&c2py::wrap_pytype<_c2py_cls_c70bfb85>) < 0) return NULL;
  if (PyType_Ready(&c2py::wrap_pytype<_c2py_cls_c60bf9f2>) < 0) return NULL;

  m = PyModule_Create(&module_def);
  if (m == NULL) return NULL;

  if (not c2py::register_internal_types()) return NULL;
#define _add_type(T, N)                                                                                                                              \
  if (not c2py::add_type_object_to_main<T>(N, m)) return NULL
  _add_type(_c2py_cls_c40bf6cc, "A");
  _add_type(_c2py_cls_c70bfb85, "B");
  _add_type(_c2py_cls_c60bf9f2, "C");
#undef _add_type

  return m;
}
#endif
// CLAIR_WRAP_GEN

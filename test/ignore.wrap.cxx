
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

// --------- class _c2py_cls_0ce9aeec -----------
using _c2py_cls_0ce9aeec                                            = a_struct;
template <> constexpr bool c2py::is_wrapped<_c2py_cls_0ce9aeec>     = true;
template <> inline constexpr auto c2py::tp_name<_c2py_cls_0ce9aeec> = "ignore.AStruct";

static int synth_constructor_923ff529(PyObject *self, PyObject *args, PyObject *kwargs) {
  if (args and PyTuple_Check(args) and (PyTuple_Size(args) > 0)) {
    PyErr_SetString(PyExc_RuntimeError, ("Error in constructing a_struct.\nNo positional arguments allowed. Use keywords arguments"));
    return -1;
  }
  c2py::pydict_extractor de{kwargs};
  try {
    ((c2py::wrap<_c2py_cls_0ce9aeec> *)self)->_c = new _c2py_cls_0ce9aeec{};
  } catch (std::exception const &e) {
    PyErr_SetString(PyExc_RuntimeError, ("Error in constructing a_struct from a Python dict.\n   "s + e.what()).c_str());
    return -1;
  }
  auto &self_c = *(((c2py::wrap<_c2py_cls_0ce9aeec> *)self)->_c);
  de("a", self_c.a, false);
  return de.check();
}

template <> constexpr initproc c2py::tp_init<_c2py_cls_0ce9aeec> = synth_constructor_923ff529;

template <>
const std::string c2py::tp_ctor_doc<_c2py_cls_0ce9aeec> = c2py::replace_tags(R"DOC(Synthesized constructor with the following keyword arguments:

Parameters
----------
a : {par_0}

)DOC",
                                                                             "par", {c2py::python_typename<int>()});

// ----- Method table ----
// clang-format off
template <> PyMethodDef c2py::tp_methods<_c2py_cls_0ce9aeec>[] = {
   {nullptr, nullptr, 0, nullptr} // Sentinel
};
// clang-format on

constexpr auto _c2py_doc_member_fae1ab4b = R"DOC()DOC";
static PyObject *prop_get_dict_923ff529(PyObject *self, void *) {
  auto &self_c = *(((c2py::wrap<_c2py_cls_0ce9aeec> *)self)->_c);
  c2py::pydict dic;
  dic["a"] = self_c.a;
  return dic.new_ref();
}

// ----- Member and property table ----

template <>
constinit PyGetSetDef c2py::tp_getset<_c2py_cls_0ce9aeec>[] = {
   c2py::getsetdef_from_member<&_c2py_cls_0ce9aeec::a, _c2py_cls_0ce9aeec>("a", _c2py_doc_member_fae1ab4b),
   {"__dict__", (getter)prop_get_dict_923ff529, nullptr, "", nullptr},
   {nullptr, nullptr, nullptr, nullptr, nullptr}};

template <> const std::string c2py::tp_doc<_c2py_cls_0ce9aeec> = R"DOC()DOC" + c2py::tp_ctor_doc<_c2py_cls_0ce9aeec>;
// --------- class _c2py_cls_6f15601e -----------
using _c2py_cls_6f15601e                                            = opaque;
template <> constexpr bool c2py::is_wrapped<_c2py_cls_6f15601e>     = true;
template <> inline constexpr auto c2py::tp_name<_c2py_cls_6f15601e> = "ignore.Opaque";
static const auto _c2py_init_41eecd22                               = c2py::dispatcher_c_kw_t{c2py::c_constructor<_c2py_cls_6f15601e>()};
template <> constexpr initproc c2py::tp_init<_c2py_cls_6f15601e>    = c2py::pyfkw_constructor<_c2py_init_41eecd22>;
template <> const std::string c2py::tp_ctor_doc<_c2py_cls_6f15601e> = _c2py_init_41eecd22.doc(R"DOC()DOC");

// ----- Method table ----
// clang-format off
template <> PyMethodDef c2py::tp_methods<_c2py_cls_6f15601e>[] = {
   {nullptr, nullptr, 0, nullptr} // Sentinel
};
// clang-format on

template <> const std::string c2py::tp_doc<_c2py_cls_6f15601e> = R"DOC()DOC" + c2py::tp_ctor_doc<_c2py_cls_6f15601e>;
// --------- class _c2py_cls_0aa66544 -----------
using _c2py_cls_0aa66544                                            = opaque2;
template <> constexpr bool c2py::is_wrapped<_c2py_cls_0aa66544>     = true;
template <> inline constexpr auto c2py::tp_name<_c2py_cls_0aa66544> = "ignore.Opaque2";
static const auto _c2py_init_2b8f7f95                               = c2py::dispatcher_c_kw_t{c2py::c_constructor<_c2py_cls_0aa66544>()};
template <> constexpr initproc c2py::tp_init<_c2py_cls_0aa66544>    = c2py::pyfkw_constructor<_c2py_init_2b8f7f95>;
template <> const std::string c2py::tp_ctor_doc<_c2py_cls_0aa66544> = _c2py_init_2b8f7f95.doc(R"DOC()DOC");

// ----- Method table ----
// clang-format off
template <> PyMethodDef c2py::tp_methods<_c2py_cls_0aa66544>[] = {
   {nullptr, nullptr, 0, nullptr} // Sentinel
};
// clang-format on

template <> const std::string c2py::tp_doc<_c2py_cls_0aa66544> = R"DOC()DOC" + c2py::tp_ctor_doc<_c2py_cls_0aa66544>;

// ==================== module functions ====================

// inc_opaque
static auto const _c2py_fun_633491bb = c2py::dispatcher_f_kw_t{c2py::cfun([](opaque &w) { return inc_opaque(w); }, "w")};

// inc_opaque2
static auto const _c2py_fun_b4c11aab = c2py::dispatcher_f_kw_t{c2py::cfun([](opaque2 &w) { return inc_opaque2(w); }, "w")};

// make_opaque
static auto const _c2py_fun_f7931ad3 = c2py::dispatcher_f_kw_t{c2py::cfun([]() { return make_opaque(); })};

// make_opaque2
static auto const _c2py_fun_9d935033 = c2py::dispatcher_f_kw_t{c2py::cfun([]() { return make_opaque2(); })};

// take_opaque
static auto const _c2py_fun_9f181a08 = c2py::dispatcher_f_kw_t{c2py::cfun([](const opaque &w) { return take_opaque(w); }, "w")};

// take_opaque2
static auto const _c2py_fun_acf1494e = c2py::dispatcher_f_kw_t{c2py::cfun([](const opaque2 &w) { return take_opaque2(w); }, "w")};

static const auto _c2py_doc_633491bb = _c2py_fun_633491bb.doc(R"DOC()DOC");
static const auto _c2py_doc_b4c11aab = _c2py_fun_b4c11aab.doc(R"DOC()DOC");
static const auto _c2py_doc_f7931ad3 = _c2py_fun_f7931ad3.doc(R"DOC()DOC");
static const auto _c2py_doc_9d935033 = _c2py_fun_9d935033.doc(R"DOC()DOC");
static const auto _c2py_doc_9f181a08 = _c2py_fun_9f181a08.doc(R"DOC()DOC");
static const auto _c2py_doc_acf1494e = _c2py_fun_acf1494e.doc(R"DOC()DOC");
//--------------------- module function table  -----------------------------

// clang-format off
static PyMethodDef module_methods[] = {
   PMDF("inc_opaque", 633491bb),
   PMDF("inc_opaque2", b4c11aab),
   PMDF("make_opaque", f7931ad3),
   PMDF("make_opaque2", 9d935033),
   PMDF("take_opaque", 9f181a08),
   PMDF("take_opaque2", acf1494e),
   {nullptr, nullptr, 0, nullptr}  // Sentinel
};
// clang-format on

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

  if (PyType_Ready(&c2py::wrap_pytype<_c2py_cls_0ce9aeec>) < 0) return NULL;
  if (PyType_Ready(&c2py::wrap_pytype<_c2py_cls_6f15601e>) < 0) return NULL;
  if (PyType_Ready(&c2py::wrap_pytype<_c2py_cls_0aa66544>) < 0) return NULL;

  m = PyModule_Create(&module_def);
  if (m == NULL) return NULL;

  if (not c2py::register_internal_types()) return NULL;
#define _add_type(T, N)                                                                                                                              \
  if (not c2py::add_type_object_to_main<T>(N, m)) return NULL
  _add_type(_c2py_cls_0ce9aeec, "AStruct");
  _add_type(_c2py_cls_6f15601e, "Opaque");
  _add_type(_c2py_cls_0aa66544, "Opaque2");
#undef _add_type

  return m;
}
#endif
// CLAIR_WRAP_GEN

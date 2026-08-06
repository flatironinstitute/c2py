
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
template <> inline constexpr auto c2py::tp_name<_c2py_cls_0ce9aeec> = "pointer.AStruct";

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
  de("a", self_c.a, true);
  return de.check();
}

template <> constexpr initproc c2py::tp_init<_c2py_cls_0ce9aeec> = synth_constructor_923ff529;

template <>
const std::string c2py::tp_ctor_doc<_c2py_cls_0ce9aeec> = c2py::replace_tags(R"DOC(Synthesized constructor with the following keyword arguments:

Parameters
----------
a : {par_0}, default=30

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

// ==================== module functions ====================

// inc
static auto const _c2py_fun_a8e99c47 = c2py::dispatcher_f_kw_t{c2py::cfun([](a_struct *a) { return inc(a); }, "a")};

// read
static auto const _c2py_fun_cedfa3c5 = c2py::dispatcher_f_kw_t{c2py::cfun([](const a_struct *a) { return read(a); }, "a")};

static const auto _c2py_doc_a8e99c47 = _c2py_fun_a8e99c47.doc(R"DOC()DOC");
static const auto _c2py_doc_cedfa3c5 = _c2py_fun_cedfa3c5.doc(R"DOC()DOC");
//--------------------- module function table  -----------------------------

// clang-format off
static PyMethodDef module_methods[] = {
   PMDF("inc", a8e99c47),
   PMDF("read", cedfa3c5),
   {nullptr, nullptr, 0, nullptr}  // Sentinel
};
// clang-format on

//--------------------- module struct & init error definition ------------

//// module doc directly in the code or "" if not present...
/// Or mandatory ?
static struct PyModuleDef module_def = {PyModuleDef_HEAD_INIT,
                                        "pointer",         /* name of module */
                                        R"RAWDOC()RAWDOC", /* module documentation, may be NULL */
                                        -1, /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
                                        module_methods,
                                        NULL,
                                        NULL,
                                        NULL,
                                        NULL};

//--------------------- module init function -----------------------------

extern "C" __attribute__((visibility("default"))) PyObject *PyInit_pointer() {

  if (not c2py::check_python_version("pointer")) return NULL;

  // import numpy iff 'numpy/arrayobject.h' included
#ifdef Py_ARRAYOBJECT_H
  import_array();
#endif

  PyObject *m;

  if (PyType_Ready(&c2py::wrap_pytype<_c2py_cls_0ce9aeec>) < 0) return NULL;

  m = PyModule_Create(&module_def);
  if (m == NULL) return NULL;

  if (not c2py::register_internal_types()) return NULL;
#define _add_type(T, N)                                                                                                                              \
  if (not c2py::add_type_object_to_main<T>(N, m)) return NULL
  _add_type(_c2py_cls_0ce9aeec, "AStruct");
#undef _add_type

  return m;
}
#endif
// CLAIR_WRAP_GEN


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

// f1
static auto const _c2py_fun_0 = c2py::dispatcher_f_kw_t{c2py::cfun([](int x) { return f1(x); }, "x")};

// f10
static auto const _c2py_fun_1 = c2py::dispatcher_f_kw_t{c2py::cfun([](int x) { return f10(x); }, "x")};

// f11
static auto const _c2py_fun_2 = c2py::dispatcher_f_kw_t{c2py::cfun([](int x) { return f11(x); }, "x")};

// f12
static auto const _c2py_fun_3 = c2py::dispatcher_f_kw_t{c2py::cfun([](int x) { return f12(x); }, "x")};

// f13
static auto const _c2py_fun_4 = c2py::dispatcher_f_kw_t{c2py::cfun([](int x) { return f13(x); }, "x")};

// f2
static auto const _c2py_fun_5 = c2py::dispatcher_f_kw_t{c2py::cfun([](int x) { return f2(x); }, "x")};

// f3
static auto const _c2py_fun_6 = c2py::dispatcher_f_kw_t{c2py::cfun([](int x) { return f3(x); }, "x")};

// f4
static auto const _c2py_fun_7 = c2py::dispatcher_f_kw_t{c2py::cfun([](int x) { return f4(x); }, "x")};

// f5
static auto const _c2py_fun_8 = c2py::dispatcher_f_kw_t{c2py::cfun([](int x) { return f5(x); }, "x")};

// f6
static auto const _c2py_fun_9 = c2py::dispatcher_f_kw_t{c2py::cfun([](int x) { return f6(x); }, "x")};

// f7
static auto const _c2py_fun_10 = c2py::dispatcher_f_kw_t{c2py::cfun([](int x) { return f7(x); }, "x")};

// f8
static auto const _c2py_fun_11 = c2py::dispatcher_f_kw_t{c2py::cfun([](int x) { return f8(x); }, "x")};

// f9
static auto const _c2py_fun_12 = c2py::dispatcher_f_kw_t{c2py::cfun([](int x) { return f9(x); }, "x")};

static const auto _c2py_doc_0  = _c2py_fun_0.doc(R"DOC()DOC");
static const auto _c2py_doc_1  = _c2py_fun_1.doc(R"DOC(
Warning:

.. warning::

   Warning - line 1.
   Warning - line 2.

After warning.
)DOC");
static const auto _c2py_doc_2  = _c2py_fun_2.doc(R"DOC(
Parameters
----------
x : {par_0}
   Parameter - line 1.
   Parameter - line 2.
)DOC",
                                                 {{c2py::python_typename<int>()}});
static const auto _c2py_doc_3  = _c2py_fun_3.doc(R"DOC(
Returns
-------
{ret_0}
   Return - line 1.
   Return - line 2.
)DOC",
                                                 {}, {c2py::python_typename<int>()});
static const auto _c2py_doc_4  = _c2py_fun_4.doc(R"DOC(
Brief - line 1.
Brief - line 2.

Details - line 1.
Details - line 2.

Multiline math: 

.. math::

   x = 3.1415 \; .

List 1:
* List 1 - item 1.
* List 1 - item 2.

  * List 1 - item 2.1.

* List 1 - item 3.

After list.

Parameters
----------
x : {par_0}
   Parameter - line 1.

Returns
-------
{ret_0}
   Return - line 1.
)DOC",
                                                 {{c2py::python_typename<int>()}}, {c2py::python_typename<int>()});
static const auto _c2py_doc_5  = _c2py_fun_5.doc(R"DOC(
Implicit details - line 1.
)DOC");
static const auto _c2py_doc_6  = _c2py_fun_6.doc(R"DOC(
Implicit details - line 1.

Implicit details - line 2.
)DOC");
static const auto _c2py_doc_7  = _c2py_fun_7.doc(R"DOC(
Explicit brief - line 1.
Explicit brief - line 2.

Explicit details - line 1.
Explicit details - line 2.

Implicit details - line 1.
)DOC");
static const auto _c2py_doc_8  = _c2py_fun_8.doc(R"DOC(
Inline math: :math:`x = 3.1415`.
)DOC");
static const auto _c2py_doc_9  = _c2py_fun_9.doc(R"DOC(
Multiline math:

.. math::

   x = 3.1415 \; .

After math.
)DOC");
static const auto _c2py_doc_10 = _c2py_fun_10.doc(R"DOC(
Math environment:

.. math::

   \begin{eqnarray*}
   x &= 3.1415 \; ,
   y &= 2.7182 \; .
   \end{eqnarray*}

After math.
)DOC");
static const auto _c2py_doc_11 = _c2py_fun_11.doc(R"DOC(
Code block:

::

   #include <iostream>
   int main() {
     std::cout << "Hello, world!" << std::endl;
   }

After code.
)DOC");
static const auto _c2py_doc_12 = _c2py_fun_12.doc(R"DOC(
Note:

.. note::

   Note - line 1.
   Note - line 2.

After note.
)DOC");
//--------------------- module function table  -----------------------------

static PyMethodDef module_methods[] = {
   {"f1", (PyCFunction)c2py::pyfkw<_c2py_fun_0>, METH_VARARGS | METH_KEYWORDS, _c2py_doc_0.c_str()},
   {"f10", (PyCFunction)c2py::pyfkw<_c2py_fun_1>, METH_VARARGS | METH_KEYWORDS, _c2py_doc_1.c_str()},
   {"f11", (PyCFunction)c2py::pyfkw<_c2py_fun_2>, METH_VARARGS | METH_KEYWORDS, _c2py_doc_2.c_str()},
   {"f12", (PyCFunction)c2py::pyfkw<_c2py_fun_3>, METH_VARARGS | METH_KEYWORDS, _c2py_doc_3.c_str()},
   {"f13", (PyCFunction)c2py::pyfkw<_c2py_fun_4>, METH_VARARGS | METH_KEYWORDS, _c2py_doc_4.c_str()},
   {"f2", (PyCFunction)c2py::pyfkw<_c2py_fun_5>, METH_VARARGS | METH_KEYWORDS, _c2py_doc_5.c_str()},
   {"f3", (PyCFunction)c2py::pyfkw<_c2py_fun_6>, METH_VARARGS | METH_KEYWORDS, _c2py_doc_6.c_str()},
   {"f4", (PyCFunction)c2py::pyfkw<_c2py_fun_7>, METH_VARARGS | METH_KEYWORDS, _c2py_doc_7.c_str()},
   {"f5", (PyCFunction)c2py::pyfkw<_c2py_fun_8>, METH_VARARGS | METH_KEYWORDS, _c2py_doc_8.c_str()},
   {"f6", (PyCFunction)c2py::pyfkw<_c2py_fun_9>, METH_VARARGS | METH_KEYWORDS, _c2py_doc_9.c_str()},
   {"f7", (PyCFunction)c2py::pyfkw<_c2py_fun_10>, METH_VARARGS | METH_KEYWORDS, _c2py_doc_10.c_str()},
   {"f8", (PyCFunction)c2py::pyfkw<_c2py_fun_11>, METH_VARARGS | METH_KEYWORDS, _c2py_doc_11.c_str()},
   {"f9", (PyCFunction)c2py::pyfkw<_c2py_fun_12>, METH_VARARGS | METH_KEYWORDS, _c2py_doc_12.c_str()},
   {nullptr, nullptr, 0, nullptr} // Sentinel
};

//--------------------- module struct & init error definition ------------

//// module doc directly in the code or "" if not present...
/// Or mandatory ?
static struct PyModuleDef module_def = {PyModuleDef_HEAD_INIT,
                                        "doc",             /* name of module */
                                        R"RAWDOC()RAWDOC", /* module documentation, may be NULL */
                                        -1, /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
                                        module_methods,
                                        NULL,
                                        NULL,
                                        NULL,
                                        NULL};

//--------------------- module init function -----------------------------

extern "C" __attribute__((visibility("default"))) PyObject *PyInit_doc() {

  if (not c2py::check_python_version("doc")) return NULL;

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

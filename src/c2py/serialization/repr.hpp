#pragma once
#include "../py_converter.hpp"
#include "../converters/basic_types.hpp"
#include "../converters/stl/vector.hpp"
#include "../pytypes/wrap.hpp"

using namespace std::string_literals;
static constexpr char *module_name(); // forward

namespace c2py {

  // *****************************************************************
  //  Serialization via repr
  // *****************************************************************

  // ---------------   getstate_repr ----------------------------
  //
  template <typename T>
  static constexpr PyCFunction getstate_repr = [](PyObject *self, PyObject *) -> PyObject * {
    auto &self_c = py_converter<T>::py2c(self);
    return PyObject_Repr(self);
  };

  // ---------------  setstate_repr  ----------------------------
  //
  template <typename T>
  static constexpr PyCFunction setstate_repr = [](PyObject * /*self*/, PyObject *state) -> PyObject * {
    try {
      pyref this_module = PyImport_ImportModule(module_name());
      if (this_module.is_null()) {
        PyErr_SetString(PyExc_ImportError, "Non sense ! I can not import myself ??");
        return nullptr;
      }
      PyObject *global_dict = PyModule_GetDict(this_module); //borrowed
      if (!PyUnicode_Check(state)) {
        PyErr_SetString(PyExc_RuntimeError, "Internal error");
        return nullptr;
      }
      pyref code       = Py_CompileString(PyUnicode_AsUTF8(state), "nofile", Py_eval_input);
      pyref local_dict = PyDict_New();
      return PyEval_EvalCode(code, global_dict, local_dict);
    } catch (std::exception const &e) {
      PyErr_SetString(PyExc_RuntimeError, ("in deserialization of object "s + tp_name<T>).c_str());
      return nullptr;
    }
  };

} // namespace c2py

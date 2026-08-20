#pragma once
#include "../py_converter.hpp"
#include "../converters/basic_types.hpp"
#include "../converters/stl/vector.hpp"
#include "../pytypes/wrap.hpp"

using namespace std::string_literals;

namespace c2py {

  // *****************************************************************
  //  Serialization via repr
  // *****************************************************************

  // ---------------   getstate_repr ----------------------------
  //
  template <typename T> static constexpr PyCFunction getstate_repr = [](PyObject *self, PyObject *) -> PyObject * { return PyObject_Repr(self); };

  // ---------------  setstate_repr  ----------------------------
  // The repr is evaluated in the module the class is wrapped in, as deduced from tp_name<T>.
  //
  template <typename T>
  static constexpr PyCFunction setstate_repr = [](PyObject *self, PyObject *state) -> PyObject * {
    try {
      if (!PyUnicode_Check(state)) {
        PyErr_SetString(PyExc_TypeError, ("in deserialization of object " + tp_name_str<T>() + " : expected a string state").c_str());
        return nullptr;
      }
      std::string mod_name = tp_name<T> ? package_name(tp_name<T>) : "";
      if (mod_name.empty()) {
        PyErr_SetString(PyExc_RuntimeError, "in deserialization via repr : the class has no module qualified tp_name");
        return nullptr;
      }
      pyref this_module = pyref::module(mod_name); // sets ImportError itself
      if (this_module.is_null()) return nullptr;

      PyObject *global_dict = PyModule_GetDict(this_module); //borrowed
      pyref code            = Py_CompileString(PyUnicode_AsUTF8(state), "nofile", Py_eval_input);
      if (code.is_null()) return nullptr;
      pyref local_dict = PyDict_New();
      pyref res        = PyEval_EvalCode(code, global_dict, local_dict);
      if (res.is_null()) return nullptr;
      if (!py_converter<T>::is_convertible(res, true)) return nullptr;

      ((wrap<T> *)self)->_c = new T{py_converter<T>::py2c(res)}; //NOLINT
      Py_RETURN_NONE;
    } catch (std::exception const &e) {
      PyErr_SetString(PyExc_RuntimeError, ("in deserialization of object " + tp_name_str<T>()).c_str());
      return nullptr;
    }
  };

} // namespace c2py

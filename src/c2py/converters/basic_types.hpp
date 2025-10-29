// Copyright (c) 2017 Commissariat à l'énergie atomique et aux énergies alternatives (CEA)
// Copyright (c) 2017 Centre national de la recherche scientifique (CNRS)
// Copyright (c) 2020 Simons Foundation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0.txt
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Authors: Olivier Parcollet, Nils Wentzell

#pragma once
#include <cstddef>
#include <cstdint>
#include <limits>
#include "../py_converter.hpp"
#include "../pyref.hpp"
#include "../util/numpy_includer.hpp"

namespace c2py {

  // PyObject *
  template <> struct py_converter<PyObject *> {
    static PyObject *c2py(PyObject *ob) { return ob; }
    static PyObject *py2c(PyObject *ob) { return ob; }
    static bool is_convertible(PyObject *, bool) { return true; }
  };

  // pyref
  template <> struct py_converter<pyref> {
    static PyObject *c2py(pyref const &x) { return x.new_ref(); }
    static pyref py2c(PyObject *ob) { return pyref::borrowed(ob); }
    static bool is_convertible(PyObject *, bool) { return true; }
  };

  // --- bool
  template <> struct py_converter<bool> {
    static constexpr const char *tp_name = "bool";
    static PyObject *c2py(bool b) {
      if (b)
        Py_RETURN_TRUE;
      else
        Py_RETURN_FALSE;
    }
    static bool py2c(PyObject *ob) { return ob == Py_True; }
    static bool is_convertible(PyObject *ob, bool raise_exception) {
      if (PyBool_Check(ob)) return true;
      if (raise_exception) { PyErr_SetString(PyExc_TypeError, ("Cannot convert "s + to_string(ob) + " to bool"s).c_str()); }
      return false;
    }
  };

  // --- long

  namespace details {
    template <typename I> struct py_converter_impl {

      static constexpr const char *tp_name = "int";

      static PyObject *c2py(I i) {
        if constexpr (std::is_signed_v<I>) {
          return PyLong_FromLongLong(static_cast<long long>(i));
        } else {
          return PyLong_FromUnsignedLongLong(static_cast<unsigned long long>(i));
        }
      }

      static I py2c(PyObject *ob) {
        if (PyLong_Check(ob)) {
          if constexpr (std::is_signed_v<I>) {
            return static_cast<I>(PyLong_AsLongLong(ob));
          } else {
            return static_cast<I>(PyLong_AsUnsignedLongLong(ob));
          }
        }
        // Convert NPY Scalar Type to Builtin Type
        pyref py_builtin = PyObject_CallMethod(ob, "item", nullptr); //NOLINT
        if constexpr (std::is_signed_v<I>) {
          return static_cast<I>(PyLong_AsLongLong(py_builtin));
        } else {
          return static_cast<I>(PyLong_AsUnsignedLongLong(py_builtin));
        }
      }

      static bool is_convertible(PyObject *ob, bool raise_exception) {
        // first check if ob is a python long
        if (PyLong_Check(ob)) {
          // Get value using appropriate Python C API function
          auto val = [&]() {
            if constexpr (std::is_signed_v<I>) {
              return PyLong_AsLongLong(ob);
            } else {
              return PyLong_AsUnsignedLongLong(ob);
            }
          }();

          // Check for Python errors (e.g., value out of range for long long)
          if (PyErr_Occurred()) {
            // Error is already set with appropriate message by PyLong_As*
            if (not raise_exception) PyErr_Clear();
            return false;
          }

          // Check that the value is within the limits of the target C++ type
          auto min_val = static_cast<decltype(val)>(std::numeric_limits<I>::min());
          auto max_val = static_cast<decltype(val)>(std::numeric_limits<I>::max());
          if (val < min_val or val > max_val) {
            if (raise_exception) {
              PyErr_SetString(PyExc_TypeError, ("Cannot convert "s + to_string(ob) + " to integer type, out of bounds"s).c_str());
            }
            return false;
          }
          return true;
        }

        // Check NumPy scalar types
        if (PyArray_CheckScalar(ob)) {
          pyref py_arr = PyArray_FromScalar(ob, nullptr);
          if (PyArray_ISINTEGER((PyArrayObject *)(PyObject *)py_arr)) {
            // Convert NumPy scalar to Python int and check bounds
            pyref py_int = PyObject_CallMethod(ob, "item", nullptr);
            if (not py_int) {
              if (not raise_exception) PyErr_Clear();
              return false;
            }
            // Recursively check if the converted Python int is valid
            return is_convertible(py_int, raise_exception);
          }
        }

        if (raise_exception) { PyErr_SetString(PyExc_TypeError, ("Cannot convert "s + to_string(ob) + " to integer type"s).c_str()); }
        return false;
      }
    };
  } // namespace details

  // Integer types
  // Note: Fixed-width types (int8_t, int16_t, int32_t, int64_t, uint8_t, uint16_t, uint32_t, uint64_t)
  // are typedefs to the standard types below and are automatically supported.
  template <> struct py_converter<signed char> : details::py_converter_impl<signed char> {};
  template <> struct py_converter<short> : details::py_converter_impl<short> {};
  template <> struct py_converter<int> : details::py_converter_impl<int> {};
  template <> struct py_converter<long> : details::py_converter_impl<long> {};
  template <> struct py_converter<long long> : details::py_converter_impl<long long> {};
  template <> struct py_converter<unsigned char> : details::py_converter_impl<unsigned char> {};
  template <> struct py_converter<unsigned short> : details::py_converter_impl<unsigned short> {};
  template <> struct py_converter<unsigned int> : details::py_converter_impl<unsigned int> {};
  template <> struct py_converter<unsigned long> : details::py_converter_impl<unsigned long> {};
  template <> struct py_converter<unsigned long long> : details::py_converter_impl<unsigned long long> {};

  // --- byte

  template <> struct py_converter<std::byte> {
    static constexpr const char *tp_name = "bytes";

    static PyObject *c2py(std::byte b) { return PyBytes_FromStringAndSize(reinterpret_cast<char *>(&b), 1); } //NOLINT
    static std::byte py2c(PyObject *ob) { return static_cast<std::byte>(PyBytes_AsString(ob)[0]); }           //NOLINT
    static bool is_convertible(PyObject *ob, bool raise_exception) {
      if (PyBytes_Check(ob) and PyBytes_Size(ob) == 1) return true;
      if (raise_exception) { PyErr_SetString(PyExc_TypeError, ("Cannot convert "s + to_string(ob) + " to byte"s).c_str()); }
      return false;
    }
  };

  // --- double

  template <> struct py_converter<double> {
    static constexpr const char *tp_name = "float";

    static PyObject *c2py(double x) { return PyFloat_FromDouble(x); }
    static double py2c(PyObject *ob) {
      if (PyFloat_Check(ob) || PyLong_Check(ob)) { return PyFloat_AsDouble(ob); }
      // Convert NPY Scalar Type to Builtin Type
      pyref py_builtin = PyObject_CallMethod(ob, "item", nullptr); //NOLINT
      return PyFloat_AsDouble(py_builtin);
    }
    static bool is_convertible(PyObject *ob, bool raise_exception) {
      if (PyFloat_Check(ob) || PyLong_Check(ob)) return true;
      if (PyArray_CheckScalar(ob)) {
        pyref py_arr = PyArray_FromScalar(ob, nullptr);
        if (PyArray_ISINTEGER((PyArrayObject *)(PyObject *)py_arr) or PyArray_ISFLOAT((PyArrayObject *)(PyObject *)py_arr)) return true; // NOLINT
      }
      if (raise_exception) { PyErr_SetString(PyExc_TypeError, ("Cannot convert "s + to_string(ob->ob_type) + " to double"s).c_str()); }
      return false;
    }
  };

} // namespace c2py

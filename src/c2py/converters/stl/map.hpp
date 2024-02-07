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
#include <map>
#include "./common.hpp"
#include "../../cpp_name.hpp"

namespace c2py {

  template <typename K, typename V> inline const std::string cpp_name<std::map<K, V>> = "std::map";

  template <typename K, typename V> struct py_converter<std::map<K, V>> {

    template <typename M>
    static PyObject *c2py(M &&m)
      requires(concepts::IsConvertibleC2Py<V>)
    {
      static_assert(is_instantiation_of_v<std::map, std::decay_t<M>>, "Logic Error");

      PyObject *d = PyDict_New();
      for (auto &[key, val] : m) {
        pyref k, v;
        if constexpr (std::is_reference_v<M>) {
          k = cxx2py(key);
          v = cxx2py(val);
        } else { // Map passed as rvalue
          k = cxx2py(std::move(key));
          v = cxx2py(std::move(val));
        }

        // if the K is a list, we transform into a tuple
        if (PyList_Check(k)) k = PyList_AsTuple(k);

        if (k.is_null() or v.is_null() or (PyDict_SetItem(d, k, v) == -1)) {
          Py_DECREF(d);
          return nullptr;
        } // error
      }
      return d;
    }

    // ----------------------------------------------

    static bool is_convertible(PyObject *ob, bool raise_exception) {
      if (!PyDict_Check(ob)) goto _false; //NOLINT
      {
        pyref keys   = PyDict_Keys(ob);
        pyref values = PyDict_Values(ob);
        long len     = PyDict_Size(ob);
        for (int i = 0; i < len; i++) {
          if (!py_converter<K>::is_convertible(PyList_GET_ITEM((PyObject *)keys, i), raise_exception)) goto _false;   // NOLINT borrowed ref
          if (!py_converter<V>::is_convertible(PyList_GET_ITEM((PyObject *)values, i), raise_exception)) goto _false; // NOLINT borrowed ref
        }
        return true;
      }
    _false:
      if (raise_exception) { PyErr_SetString(PyExc_TypeError, ("Cannot convert "s + to_string(ob) + " to std::map"s).c_str()); }
      return false;
    }

    // ----------------------------------------------

    static std::map<K, V> py2c(PyObject *ob)
      requires(concepts::IsConvertiblePy2C<V>)
    {
      pyref keys   = PyDict_Keys(ob);
      pyref values = PyDict_Values(ob);
      std::map<K, V> res;
      long len = PyDict_Size(ob);
      for (long i = 0; i < len; i++)
        res.emplace(py_converter<K>::py2c(PyList_GET_ITEM((PyObject *)keys, i)),    //borrowed ref
                    py_converter<V>::py2c(PyList_GET_ITEM((PyObject *)values, i))); //borrowed ref
      return res;
    }
  };
} // namespace c2py

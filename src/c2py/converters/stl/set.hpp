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
#include <set>
#include "./common.hpp"

namespace c2py {

  template <typename K> struct py_converter<std::set<K>> {

    template <typename S> static PyObject *c2py(S &&s) {
      static_assert(is_instantiation_of_v<std::set, std::decay_t<S>>, "Logic error");
      PyObject *set = PySet_New(nullptr);
      for (auto &x : s) {
        pyref y;
        if constexpr (std::is_reference_v<S>) {
          y = cxx2py(x);
        } else { // s passed as rvalue
          y = cxx2py(std::move(x));
        }
        if (y.is_null() or (PySet_Add(set, y) == -1)) {
          Py_DECREF(set);
          return nullptr;
        } // error
      }
      return set;
    }

    static bool is_convertible(PyObject *ob, bool raise_exception) {
      if (!PySet_Check(ob)) goto _false; // NOLINT
      {
        pyref keys_it = PyObject_GetIter(ob);
        pyref key;
        while (bool(key = PyIter_Next(keys_it))) {
          if (!py_converter<K>::is_convertible(key, raise_exception)) goto _false; // NOLINT borrowed ref
        }
        return true;
      }
    _false:
      if (raise_exception) { PyErr_SetString(PyExc_TypeError, ("Cannot convert "s + to_string(ob) + " to std::set"s).c_str()); }
      return false;
    }

    static std::set<K> py2c(PyObject *ob) {
      std::set<K> res;
      pyref keys_it = PyObject_GetIter(ob);
      pyref key;
      while (bool(key = PyIter_Next(keys_it))) {
        res.insert(py_converter<K>::py2c(key)); //borrowed ref
      }
      return res;
    }
  };
} // namespace c2py

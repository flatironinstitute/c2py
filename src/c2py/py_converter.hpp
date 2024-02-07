// Copyright (c) 2017-2018 Commissariat à l'énergie atomique et aux énergies alternatives (CEA)
// Copyright (c) 2017-2018 Centre national de la recherche scientifique (CNRS)
// Copyright (c) 2018-2022 Simons Foundation
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
// Authors: Philipp Dumitrescu, Olivier Parcollet, Nils Wentzell

#pragma once
#include <type_traits>
#include <exception>
#include <string>
#include <complex>
#include <map>
#include <memory>
#include <typeindex>
#include <iostream>

#include "./pyref.hpp"

// for backward compatibility layer below
namespace cpp2py {
  template <typename T> struct py_converter;
}

namespace c2py {

  //---------------------  py_converters -----------------------------

  template <typename T> struct py_converter;
#if 0
  // format of converters. NB do not uncomment, py_converter has no default implementation.
  template <typename T> struct py_converter {
   
   // From C++ to python. Can throw. FIXME : CHECK THIS? Really ? can it be noexcept ?

   static PyObject *c2py(auto &&x);
   
   // Return true iif the object can A PRIORI be converted.
   // It is a normally type check.
   // An error may still occurr in the conversion, e.g. int overflow.
   // is_convertible is used for the dynamic dispatch of the function
   // raise_exception : in case of failure, it sets an error message as a python exception ...

   static bool is_convertible(PyObject *ob, bool raise_exception) noexcept;
   
   // Convert. Assumes that is_convertible is true
   // Can still throw C++ exception.
   // Returns a T or a ref (for wrapped types).

   static [T & | T] py2c(PyObject *ob);
  };
#endif

  //---------------------  is_wrapped -----------------------------

  // This must be specialized for each wrapped type which is wrapped
  // in another module than the one currently being compiled.
  // This enables the compiler to know which type is wrapped.

  template <typename T> static constexpr bool is_wrapped = false; // default

  //---------------------  Concept to check convertibility -----------------------------

  namespace concepts {

    // IsConvertiblePy2C
    template <typename U>
    concept IsConvertiblePy2C = requires() {
      { c2py::py_converter<std::decay_t<U>>::py2c((PyObject *)nullptr) } -> std::convertible_to<U>;
      { c2py::py_converter<std::decay_t<U>>::is_convertible((PyObject *)nullptr, false) } -> std::same_as<bool>;
    };

    // IsConvertibleC2Py
    template <typename U>
    concept IsConvertibleC2Py = requires(U x) {
      { c2py::py_converter<std::remove_const_t<U>>::c2py(x) } -> std::same_as<PyObject *>;
    };

    // IsConvertible
    template <typename U>
    concept IsConvertible = IsConvertibleC2Py<U> and IsConvertiblePy2C<U>;

  } // namespace concepts
  //---------------------  Helper functions -----------------------------

  // Convert a PyObject to C++
  // NB: can return a T or  T [const] & (for wrapped types)
  template <typename T> static decltype(auto) py2cxx(PyObject *x) { return py_converter<std::decay_t<T>>::py2c(x); }

  // Convert a C++ object into a Python object (always a NEW REFERENCE)
  template <typename T> static PyObject *cxx2py(T &&x) { return py_converter<std::decay_t<T>>::c2py(std::forward<T>(x)); }

  // True iif the object ob is convertible into T (short cut)
  // raise_exception. Cf py_converter::is_convertible
  template <typename T> static bool convertible(PyObject *ob, bool raise_exception) { return py_converter<T>::is_convertible(ob, raise_exception); }

  // ---------------------  Backward compatibility layer with cpp2py ------------
  // If the converters already exists in cpp2py, use them

  namespace concepts {
    template <typename U>
    concept IsConvertibleCPP2Py_backwd = requires(U x) {
      { cpp2py::py_converter<std::remove_const_t<U>>::c2py(x) } -> std::same_as<PyObject *>;
    } and not requires { typename cpp2py::py_converter<std::remove_const_t<U>>::is_wrapped_type; };
    // types wrapped by cpp2y ARE convertible, but using the same default mechanism as for c2py
    // provided we have declared that is_wrapped is true for them
    // so we do not use the generic cpp2py py_converter below.
  } // namespace concepts

  template <typename T>
    requires(concepts::IsConvertibleCPP2Py_backwd<std::decay_t<T>>)
  struct py_converter<T> : ::cpp2py::py_converter<std::decay_t<T>> {};

} // namespace c2py

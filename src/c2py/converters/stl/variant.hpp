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
#include <tuple>
#include <variant>
#include "./common.hpp"

namespace c2py {

  // std::variant<T...> converter
  // converts in the first possible type
  template <typename... T> struct py_converter<std::variant<T...>> {

    private:
    template <int N> using types_t = std::tuple_element_t<N, std::tuple<T...>>;

    template <int N> static std::variant<T...> py2c_impl(PyObject *ob) {
      using conv = py_converter<std::tuple_element_t<N, std::tuple<T...>>>;
      if (conv::is_convertible(ob, false)) return conv::py2c(ob);
      if constexpr (N < sizeof...(T) - 1)
        return py2c_impl<N + 1>(ob);
      else
        throw std::runtime_error("Internal error: py2c called for a Python object incompatible with std::variant");
    }

    // struct _visitor {
    //   template <typename U> PyObject *operator()(U &&x) { return cxx2py(std::forward<U>(x)); }
    // };

    public:
    template <typename V> static PyObject *c2py(V &&v) {
      static_assert(is_instantiation_of_v<std::variant, std::decay_t<V>>);
      // return visit(_visitor{}, std::forward<V>(v));
      return visit([]<typename U>(U &&x) { return cxx2py(std::forward<U>(x)); }, std::forward<V>(v));
    }

    static bool is_convertible(PyObject *ob, bool raise_exception) {
      if ((... or py_converter<std::decay_t<T>>::is_convertible(ob, false))) return true;
      if (raise_exception) { PyErr_SetString(PyExc_TypeError, ("Cannot convert "s + to_string(ob) + " to std::variant"s).c_str()); }
      return false;
    }

    static std::variant<T...> py2c(PyObject *ob) { return py2c_impl<0>(ob); }
  };

} // namespace c2py

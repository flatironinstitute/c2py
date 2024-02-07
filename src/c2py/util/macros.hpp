// Copyright (c) 2022 Simons Foundation
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
// Authors: Olivier Parcollet

#ifndef _CCQ_MACROS_GUARD_82h3uhru23h_H
#define _CCQ_MACROS_GUARD_82h3uhru23h_H

// CCQ, TRIQS general macros
// GUARD IT do not use pragma once
// hence one can simply include them in every projects

// -----------------------------------------------------------

#define FORCEINLINE __inline__ __attribute__((always_inline))

#ifdef NDEBUG

#define C2PY_EXPECTS(X)
#define C2PY_ASSERT(X)
#define C2PY_ENSURES(X)
#define C2PY_EXPECTS_WITH_MESSAGE(X, ...)
#define C2PY_ASSERT_WITH_MESSAGE(X, ...)
#define C2PY_ENSURES_WITH_MESSAGE(X, ...)

#else

#include <iostream>

#define C2PY_EXPECTS(X)                                                                                                                              \
  if (!(X)) {                                                                                                                                        \
    std::cerr << "Precondition " << AS_STRING(X) << " violated at " << __FILE__ << ":" << __LINE__ << "\n";                                          \
    std::terminate();                                                                                                                                \
  }
#define C2PY_ASSERT(X)                                                                                                                               \
  if (!(X)) {                                                                                                                                        \
    std::cerr << "Assertion " << AS_STRING(X) << " violated at " << __FILE__ << ":" << __LINE__ << "\n";                                             \
    std::terminate();                                                                                                                                \
  }
#define C2PY_ENSURES(X)                                                                                                                              \
  if (!(X)) {                                                                                                                                        \
    std::cerr << "Postcondition " << AS_STRING(X) << " violated at " << __FILE__ << ":" << __LINE__ << "\n";                                         \
    std::terminate();                                                                                                                                \
  }

#define C2PY_EXPECTS_WITH_MESSAGE(X, ...)                                                                                                            \
  if (!(X)) {                                                                                                                                        \
    std::cerr << "Precondition " << AS_STRING(X) << " violated at " << __FILE__ << ":" << __LINE__ << "\n";                                          \
    std::cerr << "Error message : " << __VA_ARGS__ << std::endl;                                                                                     \
    std::terminate();                                                                                                                                \
  }
#define C2PY_ASSERT_WITH_MESSAGE(X, ...)                                                                                                             \
  if (!(X)) {                                                                                                                                        \
    std::cerr << "Assertion " << AS_STRING(X) << " violated at " << __FILE__ << ":" << __LINE__ << "\n";                                             \
    std::cerr << "Error message : " << __VA_ARGS__ << std::endl;                                                                                     \
    std::terminate();                                                                                                                                \
  }
#define C2PY_ENSURES_WITH_MESSAGE(X, ...)                                                                                                            \
  if (!(X)) {                                                                                                                                        \
    std::cerr << "Postcondition " << AS_STRING(X) << " violated at " << __FILE__ << ":" << __LINE__ << "\n";                                         \
    std::cerr << "Error message : " << __VA_ARGS__ << std::endl;                                                                                     \
    std::terminate();                                                                                                                                \
  }

#endif

// --- Stringify macros -----

#define CLAIR_AS_STRING(...) CLAIR_AS_STRING2(__VA_ARGS__)
#define CLAIR_AS_STRING2(...) #__VA_ARGS__

#define AS_STRING(...) AS_STRING2(__VA_ARGS__)
#define AS_STRING2(...) #__VA_ARGS__

#define CLAIR_PRINT(X) std::cerr << AS_STRING(X) << " = " << X << "      at " << __FILE__ << ":" << __LINE__ << '\n'

#define CLAIR_C2PY_ADD_TYPE_OBJECT(CLS, PYNAME)                                                                                                      \
  Py_INCREF(&c2py::wrap_pytype<CLS>);                                                                                                                \
  PyModule_AddObject(m, PYNAME, (PyObject *)&c2py::wrap_pytype<CLS>);                                                                                \
  conv_table[std::type_index(typeid(CLS)).name()] = &c2py::wrap_pytype<CLS>;

#endif

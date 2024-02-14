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
// Authors: Olivier Parcollet, Nils Wentzell

#pragma once

// ONLY inclusion of Python.h
#include <stdexcept>
#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <string>
#include "./util/backwd_PyImport_GetModule.hpp"
namespace c2py {

  using namespace std::string_literals;
  bool check_python_version(long version = PY_VERSION_HEX, long version_major = PY_MAJOR_VERSION, long version_minor = PY_MINOR_VERSION,
                            long version_micro = PY_MICRO_VERSION);
  // must be in cpp. Mark the version of Python against which c2py is compiled.

  /**
   * A class to own a reference PyObject *, with proper reference counting.
   */
  class pyref {
    protected:
    PyObject *ob = nullptr; // NOLINT

    public:
    /// Null
    pyref() = default;

    /// Takes ownership of the reference
    pyref(PyObject *new_ref) : ob(new_ref) {}

    /// Makes a pyref from a borrowed ref
    static pyref borrowed(PyObject *ob) {
      Py_XINCREF(ob);
      return {ob};
    }

    /// Release the reference
    ~pyref() { Py_XDECREF(ob); }

    pyref(pyref const &p) : ob(p.ob) { Py_XINCREF(ob); }
    pyref(pyref &&p) noexcept : ob(p.ob) { p.ob = nullptr; }
    pyref &operator=(pyref const &p);
    pyref &operator=(pyref &&p) noexcept;

    /// Returns a borrowed reference
    operator PyObject *() const { return ob; }

    /// Returns a new reference to the object
    [[nodiscard]] PyObject *new_ref() const {
      Py_XINCREF(ob);
      return ob;
    }

    /// Reference counting. Number of reference to the underlying object.
    [[nodiscard]] long refcnt() const { return (ob != nullptr ? Py_REFCNT(ob) : -1); }

    /// True iif the object is not NULL
    explicit operator bool() const { return (ob != nullptr); }

    /// Type of the object or NULL
    [[nodiscard]] PyTypeObject *type() const { return (ob == nullptr ? nullptr : ob->ob_type); }

    /// Is object NULL
    [[nodiscard]] bool is_null() const { return ob == nullptr; }

    /// Is it Py_None
    [[nodiscard]] bool is_None() const { return ob == Py_None; }

    /// Returns the attribute attr_name, or null if the attribute does not exists or if this is null.
    pyref attr(const char *attr_name) {
      return (ob ? PyObject_GetAttrString(ob, attr_name) : nullptr);
    } // NULL : pass the error in chain call x.attr().attr()....

    template <typename T> T as() const;
    // implemented in py_converters.hpp

    /// Call. Returns null if the object is null.
    pyref operator()(PyObject *a1) {
      // NULL : pass the error in chain call x.attr().attr()....
      return (ob ? PyObject_CallFunctionObjArgs(ob, a1, NULL) : nullptr); //NOLINT
    }

    /// Call. Returns null if the object is null.
    pyref operator()(PyObject *a1, PyObject *a2) {
      // NULL : pass the error in chain call x.attr().attr()....
      return (ob ? PyObject_CallFunctionObjArgs(ob, a1, a2, NULL) : nullptr); //NOLINT
    }

    ///
    void dump() const { PyObject_Print(ob, stdout, Py_PRINT_RAW); }

    /// Import the module and returns a pyref to it
    static pyref module(std::string const &module_name);

    /// Make a Python string from the C++ string
    static pyref string(std::string const &s) { return PyUnicode_FromString(s.c_str()); }

    /// Make a Python Tuple from the C++ objects
    template <typename... T> static pyref make_tuple(T const &...x) { return PyTuple_Pack(sizeof...(T), static_cast<PyObject *>(x)...); }

    /// FIXME : rename : it can be anything ...

    /// gets a reference to the class cls_name in module_name
    static pyref get_class(const char *module_name, const char *cls_name, bool raise_exception);

    /// checks that ob is of type module_name.cls_name
    static bool check_is_instance(PyObject *ob, PyObject *cls, bool raise_exception);
  };

  static_assert(sizeof(pyref) == sizeof(PyObject *), "pyref must contain only a PyObject *");

  /// String repr of a Python Object.
  std::string to_string(PyObject *ob);

  /// String repr of a Python Type Object.
  std::string to_string(PyTypeObject *ob);

  /// Get the error message of the current Python exception.
  std::string get_python_error();

} // namespace c2py

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

#include "./pyref.hpp"

#include <ios>
#include <iostream>
#include "./util/macros.hpp"

namespace c2py {

  // A little safety check that the compiled Python version is the same as the one used to compile c2py
  bool check_python_version(long version, long version_major, long version_minor, long version_micro) {
    bool b = version == PY_VERSION_HEX;
    if (not b)
      std::cerr << "\n\n ******* FATAL ERROR in c2py ******** !!! \n\n The c2py library was compiled with Python version " //
                << std::hex << PY_VERSION_HEX << std::dec << " i.e. " << PY_MAJOR_VERSION << '.' << PY_MINOR_VERSION << '.' << PY_MICRO_VERSION
                << "\n but the python extension is compiled with Python version " //
                << std::hex << version << std::dec << " i.e. " << version_major << '.' << version_minor << '.' << version_micro
                << "\n They should be identical.\n\n ***********\n";
    return b;
  }

  //-------------------

  pyref &pyref::operator=(pyref const &p) {
    Py_XDECREF(ob);
    ob = p.ob;
    Py_XINCREF(ob);
    return *this;
  }

  ///
  pyref &pyref::operator=(pyref &&p) noexcept {
    Py_XDECREF(ob);
    ob   = p.ob;
    p.ob = nullptr;
    return *this;
  }

  /// Import the module and returns a pyref to it
  pyref pyref::module(std::string const &module_name) {
    // Maybe the module was already imported?
    PyObject *mod = PyImport_GetModule(PyUnicode_FromString(module_name.c_str()));

    // If not, import normally
    if (mod == nullptr) mod = PyImport_ImportModule(module_name.c_str());

    // Did we succeed?
    if (mod == nullptr) // throw std::runtime_error(std::string{"Failed to import module "} + module_name);
      PyErr_SetString(PyExc_ImportError, ("Can not import module " + module_name).c_str());

    return mod;
  }

  /// gets a reference to the class cls_name in module_name
  pyref pyref::get_class(const char *module_name, const char *cls_name, bool raise_exception) {
    pyref cls = pyref::module(module_name).attr(cls_name);
    if (cls.is_null() && raise_exception) {
      std::string s = std::string{"Cannot find "} + module_name + "." + cls_name;
      PyErr_SetString(PyExc_TypeError, s.c_str());
    }
    return cls;
  }

  /// checks that ob is of type module_name.cls_name
  bool pyref::check_is_instance(PyObject *ob, PyObject *cls, bool raise_exception) {
    int i = PyObject_IsInstance(ob, cls);
    if (i == -1) { // an error has occurred
      i = 0;
      if (!raise_exception) PyErr_Clear();
    }
    if ((i == 0) && (raise_exception)) {
      pyref cls_name_obj = PyObject_GetAttrString(cls, "__name__");
      std::string err    = "Type error. Expected ";
      err.append(PyUnicode_AsUTF8(cls_name_obj));
      PyErr_SetString(PyExc_TypeError, err.c_str());
    }
    return i;
  }

  /// String repr of a Python Object.
  std::string to_string(PyObject *ob) {
    assert(ob != nullptr);
    pyref py_str = PyObject_Str(ob);
    return PyUnicode_AsUTF8(py_str);
  }

  /// String repr of a Python Object.
  std::string to_string(PyTypeObject *ob) {
    return to_string((PyObject *)ob); //NOLINT
  }

  /// Get the error message of the current Python exception.
  std::string get_python_error() {

#if (PY_MAJOR_VERSION == 3) and (PY_MINOR_VERSION >= 12)
    c2py::pyref exc = PyErr_GetRaisedException();
    if (exc) {
      c2py::pyref exc_args = PyObject_GetAttrString(exc, "args");
      assert(exc_args);
      PyObject *arg0 = PyTuple_GetItem(exc_args, 0);
      if (PyUnicode_Check(arg0))
        return PyUnicode_AsUTF8(arg0);
      else
        return "<not utf string>";
    } else
      return {};
#else
    std::string r;
    PyObject *error_msg = nullptr, *ptype = nullptr, *ptraceback = nullptr;
    PyErr_Fetch(&ptype, &error_msg, &ptraceback);
    //PyObject_Print(ptype, stdout, Py_PRINT_RAW);
    //PyObject_Print(error_msg, stdout, Py_PRINT_RAW);
    //PyObject_Print(ptraceback, stdout, Py_PRINT_RAW);
    if (error_msg and PyUnicode_Check(error_msg)) r = PyUnicode_AsUTF8(error_msg);
    Py_XDECREF(ptype);
    Py_XDECREF(ptraceback);
    Py_XDECREF(error_msg);
    return r;
#endif
  }

} // namespace c2py

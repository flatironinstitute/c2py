#pragma once
#include "./pyref.hpp"
#include "./util/numpy_includer.hpp"

namespace c2py {
  struct pyinterpreter { // NOLINT
    bool has_initialized = false;

    pyinterpreter() {
      if (Py_IsInitialized()) return;
      has_initialized = true;
      PyStatus status;
      PyPreConfig preconfig;
      PyPreConfig_InitPythonConfig(&preconfig);
      preconfig.utf8_mode = 1;
      status              = Py_PreInitialize(&preconfig);
      if (PyStatus_Exception(status)) { Py_ExitStatusException(status); }
      Py_Initialize();
#ifdef Py_ARRAYOBJECT_H
      if (_import_array() < 0) {
        PyErr_Print();
        throw std::runtime_error("numpy.core.multiarray failed to import");
      }
#endif
    }

    ~pyinterpreter() {
      if (not has_initialized) return;
      if (Py_FinalizeEx() < 0) { exit(1); }
    }

    /// Execute code in Python intepreter and throw any Python Error
    void exec(const char *code) {
      PyRun_SimpleString(code);
      if (PyErr_Occurred()) { throw std::runtime_error{get_python_error()}; }
    }
  };
} // namespace c2py
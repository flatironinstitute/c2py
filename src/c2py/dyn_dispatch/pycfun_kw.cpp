#include "pycfun_kw.hpp"
#include "../util/str.hpp"
#include <string>
//#include "./c2py.hpp"
//#include "./signal_handler.hpp"

using c2py::exception_raised_in_python;

bool c2py::pycfun_kw::is_callable(PyObject *, PyObject *args, PyObject *kwargs, bool raise_exception) const noexcept {

  assert((args == nullptr) or PyTuple_Check(args));
  assert((kwargs == nullptr) or PyDict_Check(kwargs));

  long n_arg_max            = long(c_arguments.size());
  long n_arg_with_default_c = std::count_if(c_arguments.begin(), c_arguments.end(), [](auto const &a) { return a.has_default(); });
  long n_args               = (args == nullptr ? 0 : PyTuple_Size(args));
  long n_kwargs             = (kwargs == nullptr ? 0 : PyDict_Size(kwargs));
  long n_args_tot           = n_args + n_kwargs;

  // Check the number of arguments
  if (n_args_tot > n_arg_max) {
    if (raise_exception) {
      PyErr_SetString(PyExc_TypeError,
                      ("Too many arguments. Expected at most "s + std::to_string(n_arg_max) + " and got " + std::to_string(n_args_tot)).c_str());
    }
    return false;
  }

  if (n_args_tot < n_arg_max - n_arg_with_default_c) {
    if (raise_exception) {
      PyErr_SetString(
         PyExc_TypeError,
         ("Too few arguments. Expected at least "s + std::to_string(n_arg_max - n_arg_with_default_c) + " and got " + std::to_string(n_args_tot))
            .c_str());
    }
    return false;
  }

  // check all positional arguments for convertion
  for (int pos = 0; pos < n_args; pos++) {
    if (not c_arguments[pos].is_convertible(PyTuple_GetItem(args, pos), raise_exception)) {
      if (raise_exception) {
        auto err = get_python_error();
        PyErr_SetString(PyExc_TypeError, (c_arguments[pos].name + ": " + err).c_str());
      }
      return false;
    }
  }

  // check the remaining arguments.
  // either they are in the dict and checked, or there must be a default
  int n_picked_in_dict = 0;
  for (long pos = n_args; pos < n_arg_max; pos++) {
    auto const &a = c_arguments[pos];
    // pickup the argument in the dict using its name, if any
    PyObject *pyarg = (kwargs ? PyDict_GetItemString(kwargs, a.name.c_str()) : nullptr);
    if (pyarg != nullptr) { // if there is such an argument, is it convertible ?
      if (not a.is_convertible(pyarg, raise_exception)) return false;
      ++n_picked_in_dict;
    } else { // there is no such argument. If there is default, ok, else error.
      if (not a.has_default()) {
        if (raise_exception)
          PyErr_SetString(PyExc_TypeError, ("Argument #"s + std::to_string(pos) + "( " + a.name + ") can not be found and has no default").c_str());
        return false;
      }
    }
  }

  // Check that there are not too many arguments in the dict that have not been used
  if (n_picked_in_dict != n_kwargs) {
    if (raise_exception) {
      std::stringstream err;
      err << "The following named arguments are not recognized: ";
      for (long pos = n_args; pos < n_arg_max; pos++) {
        if (not PyDict_GetItemString(kwargs, c_arguments[pos].name.c_str())) err << c_arguments[pos].name << " ";
      }
      PyErr_SetString(PyExc_TypeError, err.str().c_str());
    }
    return false;
  }

  return true;
}

// --------------------------------

std::string c2py::pycfun_kw::signature() const {
  auto res = "("
     + join(
                c_arguments, [](auto &&a) { return a.name + ": " + trim(*a.type_name); }, ", ");
  return (this->rtype_name ? res + ") -> " + (*this->rtype_name) : res + ")");
}

// --------------------------------

// The call operator.
// call method is the low level call.
// This function takes care of exception, GIL.
PyObject *c2py::pycfun_kw::operator()(PyObject *self, PyObject *args, PyObject *kwargs) const {

  assert(is_callable(self, args, kwargs));
  //if (not is_callable(self, args, kwargs)) return nullptr;

  try {
    if (not release_GIL) {
      return call(self, args, kwargs);
    } else {
      Py_BEGIN_ALLOW_THREADS;
      try {
        return call(self, args, kwargs); //
      } catch (...) {
        // an error has occurred : clean GIL, handler and rethrow
        Py_BLOCK_THREADS; // cf python include, ceval.h, line 72 comments and below.
        throw;
      }
      Py_END_ALLOW_THREADS;
    }
  }
  // If the exception was raised in a python callback
  // this exception is raised in C++ by callable
  // we should simply do nothing and let python continue
  catch (exception_raised_in_python const &e) {
    if (not PyErr_Occurred()) {
      std::cerr << "LOGIC ERROR : Python exception should be raised by now ...";
      std::terminate();
    }
    // do nothing, the exception is raised
  } catch (std::exception const &e) {
    auto err = std::string(".. Error  : \n") + e.what();
    PyErr_SetString(PyExc_RuntimeError, err.c_str());
  } catch (const char *e) {
    auto err = std::string(".. Error  : \n") + e;
    PyErr_SetString(PyExc_RuntimeError, err.c_str());
  } catch (...) { PyErr_SetString(PyExc_RuntimeError, "Unknown exception in C++"); }
  return nullptr;
}

// --------------------------------

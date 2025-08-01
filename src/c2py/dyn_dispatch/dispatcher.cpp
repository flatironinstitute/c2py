#include "dispatcher.hpp"
#include <regex>

namespace c2py {
  template <typename Eraser, bool Constructors>
  PyObject *dispatcher_t<Eraser, Constructors>::call_impl(PyObject *self, PyObject *args, PyObject *kwargs) const {

    for (auto const &ov : ov_list)
      if (ov->is_callable(self, args, kwargs)) return ov->operator()(self, args, kwargs);

    // The call has failed. We rerun, but raising the exception in each case, and report
    std::stringstream err;
    err << "[c2py] Can not call the function with the arguments\n";
    //if (self) err << "  - " << PyUnicode_AsUTF8(pyref{PyObject_Str(self)}) << "\n";
    if (args) err << "   " << PyUnicode_AsUTF8(pyref{PyObject_Str(args)}) << "\n";
    if (kwargs) err << "   " << PyUnicode_AsUTF8(pyref{PyObject_Str(kwargs)}) << "\n";
    err << "The dispatch to C++ failed with the following error(s):\n";
    int c = 0;
    for (auto const &ov : ov_list) {
      ++c;
      ov->is_callable(self, args, kwargs, true);
      err << "[" << c << "] " << ov->signature() << "\n    -- " << c2py::get_python_error() << "\n\n";
    }
    PyErr_SetString(PyExc_TypeError, err.str().c_str());
    return nullptr;
  }

  // overload doc (string) in case only one overload ...
  // FIXME : to make generated code simpler in most cases.
  template <typename Eraser, bool Constructors> [[nodiscard]] std::string dispatcher_t<Eraser, Constructors>::doc(const char *doc_string) const {
    constexpr auto hline  = ".. raw:: html\n\n   <hr>\n";
    auto on_one_line = [](std::string const &sig) { return std::regex_replace(sig, std::regex(R"(\n\s+)"), " "); };
    std::stringstream fs;
    if (ov_list.size() == 1) {
      fs << "Dispatched C++ function: ``" << on_one_line(ov_list[0]->signature()) << "``\n\n";
    } else {
      fs << "Dispatched C++ functions:\n\n";
      int n = 1;
      for (auto const &ov : ov_list) fs << "[" << n++ << "] ``" << on_one_line(ov->signature()) << "``\n\n";
    }
    fs << hline << "\n\n" << doc_string << "\n";
    return fs.str();
  }

  template struct dispatcher_t<pycfun_kw, false>;
  template struct dispatcher_t<pycfun_kw, true>;
  template struct dispatcher_t<pycfun23, false>;
  template struct dispatcher_t<pycfun23, true>;

} // namespace c2py
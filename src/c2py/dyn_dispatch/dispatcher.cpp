#include "dispatcher.hpp"
#include "../util/str.hpp"
#include <cstddef>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

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

  template <typename Eraser, bool Constructors>
  [[nodiscard]] std::string dispatcher_t<Eraser, Constructors>::doc(const char *doc_string, std::vector<std::vector<std::string>> const &param_types,
                                                                    std::vector<std::string> const &return_types) const {
    auto format_sig = [](std::string const &sig) {
      auto tmp_res = std::regex_replace(sig, std::regex(R"(\n\s+)"), "\n        ");
      return std::regex_replace(tmp_res, std::regex(R"(\n\s+->)"), "\n     ->");
    };
    std::stringstream fs;
    fs << "Dispatched C++ " << (Constructors ? "constructor(s)" : "function(s)") << ".\n\n::\n\n";
    int n = 1;
    for (auto const &ov : ov_list) fs << "   [" << n++ << "] " << format_sig(ov->signature()) << "\n\n";
    auto param_types_joined = std::vector<std::string>{};
    for (auto const &pt : param_types) param_types_joined.push_back(join(pt, ", "));
    fs << replace_tags(replace_tags(doc_string, "par", param_types_joined), "ret", return_types) << "\n";
    return fs.str();
  }

  // ---------------------------------
  template struct dispatcher_t<pycfun_kw, false>;
  template struct dispatcher_t<pycfun_kw, true>;
  template struct dispatcher_t<pycfun23, false>;
  template struct dispatcher_t<pycfun23, true>;

  std::string replace_tags(std::string str, std::string const &tag, std::vector<std::string> const &vec) {
    std::size_t pos = 0;
    for (std::size_t i = 0; i < vec.size(); ++i) {
      std::string const placeholder = "{" + tag + "_" + std::to_string(i) + "}";
      pos                           = str.find(placeholder, pos);
      str.replace(pos, placeholder.size(), vec[i]);
      pos += vec[i].size();
    }
    return str;
  }

} // namespace c2py
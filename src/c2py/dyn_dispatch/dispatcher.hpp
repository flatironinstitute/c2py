#pragma once
#include <algorithm>
#include "pycfun_kw.hpp"
#include "binaryfunc.hpp"
namespace c2py {

  // =============== dynamic dispatcher ========================

  // Gather a set of overload and handle the calls and error reporting
  template <typename Eraser, bool Constructors = false> struct dispatcher_t {
    std::vector<std::unique_ptr<Eraser>> ov_list;

    template <typename... U> dispatcher_t(U &&...u) { ((void)ov_list.push_back(std::forward<U>(u)), ...); }

    private:
    PyObject *call_impl(PyObject *self, PyObject *args, PyObject *kwargs) const;

    public:
    // Call each overload. The first available is used.
    // if not is ok, we recall the is_callable to build a proper error with the exceptions
    auto operator()(PyObject *self, PyObject *args, PyObject *kwargs = nullptr) const {
      PyObject *r = call_impl(self, args, kwargs);
      if constexpr (not Constructors)
        return r;
      else
        return int(r == nullptr ? -1 : 0);
    }

    //
    [[nodiscard]] std::string signatures() const {
      std::stringstream fs;
      for (auto const &ov : ov_list) fs << ov->signature() << "\n";
      return fs.str();
    }

    // overload doc (string) in case only one overload ...
    // FIXME : to make generated code simpler in most cases.
    [[nodiscard]] std::string doc(const char *doc_string) const;
  };

  // ==============================

  using dispatcher_f_kw_t = dispatcher_t<pycfun_kw, false>;
  using dispatcher_c_kw_t = dispatcher_t<pycfun_kw, true>;

  // Transform a method pointer M into a `getter` type
  // of Python, cf https://docs.python.org/3/c-api/structures.html
  //
  template <auto M> static PyObject *getter_from_method(PyObject *self, void *) {
    static c2py::dispatcher_f_kw_t ovs = {c2py::cfun(M)};
    return ovs(self, nullptr, nullptr);
  }
} // namespace c2py

#pragma once
#include "../py_converter.hpp"
#include "../converters/basic_types.hpp"
#include "../converters/stl/vector.hpp"
#include "../pytypes/wrap.hpp"

using namespace std::string_literals;
static constexpr char *module_name(); // forward
using str_t = std::string;

namespace c2py {

  // *****************************************************************
  //  Serialization via the serialize method (boost like)
  //  into a tuple
  // *****************************************************************

  // ---------------   serializer  ----------------------------
  // auxiliary object to reduce the object into a tuple
  //
  struct serialize_tuple_worker {
    std::vector<PyObject *> elem;
    auto &operator&(auto &x) noexcept {
      elem.push_back(cxx2py(x));
      return *this;
    }
  };

  template <typename T> PyObject *serialize_tuple(T &x) noexcept {
    serialize_tuple_worker w;
    x.serialize(w, 0);
    long l        = long(w.elem.size());
    PyObject *tup = PyTuple_New(l);
    for (int pos = 0; pos < l; ++pos) PyTuple_SetItem(tup, pos, w.elem[pos]);
    return tup;
  }

  // ---------------   deserialize  ----------------------------
  // inverse : auxiliary object to reconstruct the object from the tuple ...
  //
  struct deserializer_tuple_worker {
    PyObject *tup = nullptr; // borrowed ref
    long pos = 0, pos_max = PyTuple_Size(tup) - 1;

    template <typename T> auto &operator&(T &x) {
      if (pos > pos_max) throw std::runtime_error{"Tuple too short in reconstruction"};
      x = py2cxx<T>(PyTuple_GetItem(tup, pos++));
      return *this;
    }
  };

  template <typename T> T deserialize_tuple(PyObject *ob) {
    T res;
    auto r = deserializer_tuple_worker{ob};
    res.serialize(r, 0);
    return std::move(res);
  }

  // ---------------   getstate_tuple ----------------------------
  // Returns a tuple with the function to call, the tuple
  //
  template <typename T>
  static constexpr PyCFunction getstate_tuple = [](PyObject *self, PyObject *) -> PyObject * {
    auto &self_c = py_converter<T>::py2c(self);
    return serialize_tuple(self_c);
  };

  // ---------------  setstate_tuple  ----------------------------
  // deserialize_tuple, deserialize_repr, ....
  //
  template <typename T>
  static constexpr PyCFunction setstate_tuple = [](PyObject *self, PyObject *state) -> PyObject * {
    //assert((args == nullptr) or PyTuple_Check(args));
    //assert(PyTuple_Size(args) ==1);
    try {
      // FIXME  cpp2py::regular_type_if_view_else_type_t<T> result;
      ((wrap<T> *)self)->_c = new T{deserialize_tuple<T>(state)}; //NOLINT
      Py_RETURN_NONE;
    } catch (std::exception const &e) {
      PyErr_SetString(PyExc_RuntimeError, ("in deserialization of object "s + tp_name<T>).c_str());
      return nullptr;
    }
  };

} // namespace c2py

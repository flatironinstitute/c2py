#include "../util/str.hpp"
#include "../py_converter.hpp"

namespace c2py {

  // Each enum must specialize this variable and return a map enum -> string
  // FIXME ? Should it be a simple vector of pair ??
  template <typename Enum> static std::map<Enum, std::string> enum_to_string; // NOLINT

  // Converter of an enum
  template <typename Enum>
    requires(std::is_enum_v<Enum>)
  struct py_converter<Enum> {
    // In python, just a string
    static PyObject *c2py(Enum x) { return PyUnicode_FromString(enum_to_string<Enum>.find(x)->second.c_str()); }

    // string -> value
    static Enum py2c(PyObject *ob) {
      static auto str_to_enum = reverse_std_map(enum_to_string<Enum>);
      std::string s           = PyUnicode_AsUTF8(ob);
      auto it                 = str_to_enum.find(s);
      return it->second;
    }

    // convertibility : must be a string
    // FIXME : the find must occur in py2c
    // and throw a C++ exception ...
    static bool is_convertible(PyObject *ob, bool raise_exception) {
      static auto str_to_enum = reverse_std_map(enum_to_string<Enum>);
      if (!PyUnicode_Check(ob)) {
        if (raise_exception) PyErr_SetString(PyExc_ValueError, "Convertion of C++ enum : the object is not a string");
        return false;
      }
      std::string s = PyUnicode_AsUTF8(ob);
      if (auto it = str_to_enum.find(s); it != str_to_enum.end()) return true;
      if (raise_exception) {
        auto err = "Convertion of C++ enum : \nThe string \"" + s + "\" is not in "
           + join(
                      enum_to_string<Enum>, [](auto &&x) { return x.second; }, ',');
        PyErr_SetString(PyExc_ValueError, err.c_str());
      }
      return false;
    }
  };

} // namespace c2py

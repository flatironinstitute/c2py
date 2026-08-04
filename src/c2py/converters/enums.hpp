#pragma once
#include "../util/str.hpp"
#include "../py_converter.hpp"

namespace c2py {

  // Each enum must specialize this variable and return a map enum -> string
  // FIXME ? Should it be a simple vector of pair ??
  template <typename Enum> static const std::map<Enum, std::string> enum_to_string; // NOLINT

  // Converter of an enum
  template <typename Enum>
    requires(std::is_enum_v<Enum> and is_wrapped<Enum>)
  struct py_converter<Enum> {
    static std::string tp_name() {
      std::ostringstream out;
      out << "str {";
      std::string sep;
      for (auto const &p : enum_to_string<Enum>) {
        out << sep << "\""<< p.second << "\"";
        sep = ", ";
      }
      out << "}";
      return out.str();
    }

    // In python, just a string.
    // x is not necessarily an enumerator : any value of the underlying type is a value of the enum
    // (e.g. Flags::A | Flags::B), and such a value has no name to convert to.
    static PyObject *c2py(Enum x) {
      auto it = enum_to_string<Enum>.find(x);
      if (it == enum_to_string<Enum>.end()) {
        PyErr_SetString(PyExc_ValueError, ("Enum " + cpp_qname<Enum>() + " : this value is not an enumerator").c_str());
        return nullptr;
      }
      return PyUnicode_FromString(it->second.c_str());
    }

    // string -> value. is_convertible has already checked the find.
    static Enum py2c(PyObject *ob) {
      static auto str_to_enum = reverse_std_map(enum_to_string<Enum>);
      std::string s           = PyUnicode_AsUTF8(ob);
      auto it                 = str_to_enum.find(s);
      if (it == str_to_enum.end()) throw std::runtime_error{"Enum " + cpp_qname<Enum>() + " : unknown string \"" + s + "\""};
      return it->second;
    }

    // convertibility : must be a string
    static bool is_convertible(PyObject *ob, bool raise_exception) {
      static auto str_to_enum = reverse_std_map(enum_to_string<Enum>);
      if (!PyUnicode_Check(ob)) {
        if (raise_exception) PyErr_SetString(PyExc_ValueError, "Conversion of a C++ enum : the object is not a string");
        return false;
      }
      std::string s = PyUnicode_AsUTF8(ob);
      if (auto it = str_to_enum.find(s); it != str_to_enum.end()) return true;
      if (raise_exception) {
        auto err = "Conversion of C++ enum : \nThe string \"" + s + "\" is not in "
           + join(
                      enum_to_string<Enum>, [](auto &&x) { return x.second; }, ',');
        PyErr_SetString(PyExc_ValueError, err.c_str());
      }
      return false;
    }
  };

} // namespace c2py

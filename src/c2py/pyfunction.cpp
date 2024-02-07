#include "./pyfunction.hpp"
//#include <format>
namespace c2py::detail {

  std::string format_error(pyref const &r, std::string const &fname, std::string const &cpp_name_R, std::string const &converter_error) {

    // FIXME : when std::format will be present in all compilers
    // Libc ++ > = 17
    // gcc  >= 13

#if 0
    return std::format(R"RAW(
Error in converting in calling the pyfunction `{}`:
  The result of type {} can not be converted to C++ type {} 
  NB: the result was

  {}
  
  The converter error was :
  {}
  )RAW",
                       fname, to_string(r.type()), cpp_name_R, to_string(r), converter_error);
#else

    return " Error in converting in calling the pyfunction `" + fname + "`:\n The result of type " + to_string(r.type())
       + " can not be converted to C++ type " + cpp_name_R + "\n NB: the result was \n \n " + to_string(r) + "   The converter error was : \n\n"
       + converter_error + "\n";
#endif
  }
} // namespace c2py::detail
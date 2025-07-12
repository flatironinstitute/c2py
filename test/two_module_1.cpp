#include <c2py/c2py.hpp>
#include "./two_module_1.hpp"

namespace c2py_module {

  auto match_names = "N::(A|f)";

}

#include "two_module_1.wrap.cxx"

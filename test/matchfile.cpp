#include <c2py/c2py.hpp>
#include "aux/matchfile_aux.hpp"

// In the main file — must NOT be wrapped
int local_f() { return 0; }

#include "matchfile.wrap.cxx"

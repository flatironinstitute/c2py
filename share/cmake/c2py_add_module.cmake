include_guard(GLOBAL)
include("${CMAKE_CURRENT_LIST_DIR}/clair_c2py_generate_bindings.cmake")

# c2py_add_module(<name>
#                 [DIR <relative-dir>]
#                 [LINK_LIBRARIES <lib1> ...]
#                 [DEPENDS_ON_BINDINGS <module1> ...])
#
# Builds <DIR>/<name>.cpp into a Python module with the SOABI suffix
# and wires up clair-c2py binding generation (gated by
# Update_Python_Bindings). DEPENDS_ON_BINDINGS names existing module
# targets whose bindings must be generated first; non-binding targets
# are skipped. For other orderings, use add_dependencies(${name} ...).
#
# Macro, not function: find_package(Python) must land in the caller's
# scope or Python_add_library WITH_SOABI silently drops the suffix.
macro(c2py_add_module _c2py_name)
  cmake_parse_arguments(_c2py "" "DIR" "LINK_LIBRARIES;DEPENDS_ON_BINDINGS" ${ARGN})
  find_package(Python REQUIRED COMPONENTS Interpreter Development.Module NumPy)

  set(_c2py_src "${_c2py_name}.cpp")
  if(_c2py_DIR)
    set(_c2py_src "${_c2py_DIR}/${_c2py_src}")
  endif()

  Python_add_library(${_c2py_name} MODULE WITH_SOABI "${_c2py_src}")
  set_target_properties(${_c2py_name} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${_c2py_DIR}"
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN ON)
  target_link_libraries(${_c2py_name} PRIVATE c2py::c2py ${_c2py_LINK_LIBRARIES})

  if(Update_Python_Bindings)
    clair_c2py_generate_bindings(${_c2py_name} DIR "${_c2py_DIR}")
    foreach(_dep ${_c2py_DEPENDS_ON_BINDINGS})
      if(NOT TARGET ${_dep})
        message(FATAL_ERROR "c2py_add_module(${_c2py_name}): DEPENDS_ON_BINDINGS target '${_dep}' does not exist")
      endif()
      if(TARGET ${_dep}_bindings_generation)
        add_dependencies(${_c2py_name}_bindings_generation ${_dep}_bindings_generation)
      endif()
    endforeach()
  endif()
endmacro()

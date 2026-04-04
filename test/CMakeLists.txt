# For clair plugin testing we need to add the LD_PRELOAD for the compilation ITSELF
if (IS_CLAIR_BUILD AND (ASAN OR UBSAN))
  message(STATUS "Adding LD_PRELOAD to the compilation to check clair plugin")
  message(STATUS "SANITIZER_RT_PRELOAD = ${SANITIZER_RT_PRELOAD}")
  set(CMAKE_CXX_COMPILER_LAUNCHER env ${SANITIZER_RT_PRELOAD})
endif()

macro(c2py_add_test modulename)
  get_filename_component(test_name ${modulename} NAME_WE)
  get_filename_component(test_dir ${modulename} DIRECTORY)
  Python_add_library(${modulename} MODULE ${modulename}.cpp)
  target_link_libraries(${modulename} PRIVATE c2py c2py_warnings)
  add_test(NAME ${modulename}_py COMMAND ${Python_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/${test_dir}/${modulename}_test.py WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${test_dir})
  set_property(TEST ${modulename}_py APPEND PROPERTY ENVIRONMENT PYTHONPATH=${h5_BINARY_DIR}/python:${CMAKE_CURRENT_BINARY_DIR}:$ENV{PYTHONPATH} ${SANITIZER_RT_PRELOAD})
  if (IS_CLAIR_BUILD AND NOT "${ARGN}" STREQUAL "LOW_LEVEL")
    # Verbose, but I don't know to make simpler: on 
    if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${modulename}.toml")
       set(toml_file_ext "toml")
    else() 
       set(toml_file_ext "cpp") # duplicates the depends, but it does not matter
    endif()
    add_custom_command(
      OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${modulename}.wrap.cxx
      COMMAND clair-c2py -p ${PROJECT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/${modulename}.cpp
      DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${modulename}.cpp 
      DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${modulename}.${toml_file_ext} 
      DEPENDS clair-c2py # If the tool ifself is recompiled, we need to regenerate the wrap.cxx
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
    add_custom_target(generate_${modulename} DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${modulename}.wrap.cxx)
    add_dependencies(${modulename} generate_${modulename})
  endif()
endmacro()

# ----------------------------
c2py_add_test(cls LOW_LEVEL)
set (c2py_all_low_level_tests cls CACHE INTERNAL "") # Keep this, used in clair 

set(c2py_all_full_tests
  any
  accessor
  properties
  basicfun
  bug_tpl_type
  cls_basic
  doc
  namespace
  cls_der
  pointer
  comparison
  config_filter
  issue9
  callables
  itertool
  ignore
  generator
  enumcxx
  integers
  synth_init
  tpl_cls
  tpl_derived
  callback
  std_container
  two_module_1
  two_module_2
  refcount
  const_ref_default_arg
  arithmetic
  deprecated_params
  tpl_default_arg
  CACHE INTERNAL "")

foreach(t ${c2py_all_full_tests})
  c2py_add_test(${t})
endforeach()

if (IS_CLAIR_BUILD)
  add_subdirectory(compilation_failure_checks)
endif()

# must compile 1 first to have the hxx of the wrapped objects
add_dependencies(two_module_2 two_module_1)

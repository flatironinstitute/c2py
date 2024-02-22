# For clair plugin testing we need to add the LD_PRELOAD for the compilation ITSELF
if (IS_CLAIR_BUILD AND (ASAN OR UBSAN))
  message(STATUS "Adding LD_PRELOAD to the compilation to check clair plugin")
  message(STATUS "SANITIZER_RT_PRELOAD = ${SANITIZER_RT_PRELOAD}")
  set(CMAKE_CXX_COMPILER_LAUNCHER env ${SANITIZER_RT_PRELOAD})
endif()

macro(c2py_add_test_1 modulename module_extension) 
  get_filename_component(test_name ${modulename} NAME_WE)
  get_filename_component(test_dir ${modulename} DIRECTORY)
  Python_add_library(${modulename} MODULE ${modulename}.${module_extension})
  target_link_libraries(${modulename} PRIVATE c2py c2py_warnings)
  add_test(NAME ${modulename}_py COMMAND ${Python_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/${test_dir}/${modulename}_test.py WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${test_dir})
  set_property(TEST ${modulename}_py APPEND PROPERTY ENVIRONMENT PYTHONPATH=${h5_BINARY_DIR}/python:${CMAKE_CURRENT_BINARY_DIR}:$ENV{PYTHONPATH} ${SANITIZER_RT_PRELOAD})
endmacro()

macro(c2py_add_test modulename)
  if(IS_CLAIR_BUILD)
    c2py_add_test_1(${modulename} cpp)
    target_link_libraries(${modulename} PRIVATE clair::c2py_plugin)
    target_compile_options(${modulename} PRIVATE -Wno-unused-const-variable -Wno-unused-variable)
  else()
    c2py_add_test_1(${modulename} wrap.cxx)
  endif()
endmacro()

#--------------------------------------------------------
#  A target to copy the wrap.cxx files back to the src
#--------------------------------------------------------

add_custom_target(c2py_copy_wrap_cxx_to_src)
add_custom_command(
  TARGET c2py_copy_wrap_cxx_to_src
  COMMAND cp ${CMAKE_CURRENT_BINARY_DIR}/*.wrap.?xx ${CMAKE_CURRENT_SOURCE_DIR}
  COMMAND echo "** Copying all wrap.cxx to c2py test"
)

# ----------------------------
set(c2py_all_low_level_tests cls CACHE INTERNAL "")
set(c2py_all_full_tests 
  annote basicfun
  cls_basic
  cls_der
  comparison
  issue9
  callables
  itertool
  generator
  enumcxx
  synth_init
  tpl_cls
  tpl_derived
  callback
  two_module_1
  two_module_2
  CACHE INTERNAL "")

foreach(t ${c2py_all_low_level_tests})
  c2py_add_test_1(${t} "cxx")  
endforeach()

foreach(t ${c2py_all_full_tests})
  c2py_add_test(${t})
endforeach()

# must compile 1 first to have the hxx of the wrapped objects
add_dependencies(two_module_2 two_module_1)

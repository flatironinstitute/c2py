#FILE(COPY ${CMAKE_SOURCE_DIR}/.clang-format DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

#find_package(sanitizer REQUIRED "asan")
#MESSAGE("SANITIZER_RT_PRELOAD = ${SANITIZER_RT_PRELOAD}")

macro(c2py_add_test_1 modulename module_extension) 

  Python_add_library( ${modulename} MODULE "${modulename}.${module_extension}")
  target_compile_options(${modulename} PRIVATE -std=c++20 )
  target_include_directories(${modulename} SYSTEM PRIVATE  ${CMAKE_SOURCE_DIR}/src)
  target_link_libraries(${modulename} PRIVATE c2py ${PROJECT_NAME}_warnings  Python::NumPy)

if(ASAN)
  target_link_libraries(${modulename}  PRIVATE $<BUILD_INTERFACE:asan>)
endif()
if(UBSAN)
  target_link_libraries(${modulename}  PRIVATE $<BUILD_INTERFACE:ubsan>)
endif()

  get_filename_component(test_name ${modulename} NAME_WE)
  get_filename_component(test_dir ${modulename} DIRECTORY)
  add_test(NAME ${modulename}_py COMMAND ${Python_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/${test_dir}/${modulename}_test.py WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${test_dir})
  set_property(TEST ${modulename}_py APPEND PROPERTY ENVIRONMENT PYTHONPATH=${h5_BINARY_DIR}/python:${CMAKE_CURRENT_BINARY_DIR}:$ENV{PYTHONPATH} ${SANITIZER_RT_PRELOAD})
endmacro()

macro(c2py_add_test modulename)
  c2py_add_test_1(${modulename} $<IF:$<TARGET_EXISTS:clair::c2py_plugin>,cpp,wrap.cxx>) 
  target_link_libraries(${modulename} PRIVATE $<TARGET_NAME_IF_EXISTS:clair::c2py_plugin>)
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
set(c2py_all_full_tests  annote basicfun cls_basic cls_der comparison issue9 callables itertool generator
    enumcxx synth_init tpl_cls tpl_derived callback two_module_1 two_module_2 CACHE INTERNAL "")

foreach(t ${c2py_all_low_level_tests} )
  c2py_add_test_1(${t} "cxx")  
endforeach()

foreach(t ${c2py_all_full_tests} )
  c2py_add_test(${t})
endforeach()

# must compile 1 first to have the hxx of the wrapped objects
add_dependencies(two_module_2 two_module_1)

# Dummy target to populate compile_commands.json for the fail test sources
add_library(clair_fail_tests_compile_db OBJECT accessor_fail.cpp fnt_notwrappable_fail.cpp)
target_link_libraries(clair_fail_tests_compile_db PRIVATE c2py)

macro(c2py_add_fail_test modulename)
  add_test(NAME ${modulename}
    COMMAND clair-c2py -p ${PROJECT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/${modulename}.cpp
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  )
  set_tests_properties(${modulename} PROPERTIES PASS_REGULAR_EXPRESSION "error:")
endmacro()

c2py_add_fail_test(accessor_fail)
c2py_add_fail_test(fnt_notwrappable_fail)

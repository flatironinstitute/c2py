function(clair_c2py_generate_bindings ModuleName)

  set(wrap_cxx "${CMAKE_CURRENT_SOURCE_DIR}/${ModuleName}.wrap.cxx")   # Python bindings file
  set(depfile "${CMAKE_CURRENT_BINARY_DIR}/${ModuleName}.cpp.d")       # dependency file

  # In-tree clair build: use the build target directly and rebuild bindings when the tool is recompiled.
  # Otherwise (downstream projects): find the installed clair-c2py in PATH.
  if (TARGET clair-c2py)
    set(_clair_c2py_cmd clair-c2py)
    set(_clair_c2py_dep clair-c2py)
  else()
    find_program(CLAIR_C2PY_EXECUTABLE clair-c2py REQUIRED)
    set(_clair_c2py_cmd ${CLAIR_C2PY_EXECUTABLE})
  endif()

  add_custom_command(
    OUTPUT ${wrap_cxx} ${depfile}                                                                          # Generates the .wrap.cxx and dependency files
    COMMAND ${_clair_c2py_cmd} -p ${PROJECT_BINARY_DIR} --generate-depfile ${depfile} ${ModuleName}.cpp     # -p path/to/compile/commands
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${ModuleName}.cpp ${_clair_c2py_dep}                               # Rebuild when source or tool changes
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}                                                          # Execute in source directory
    DEPFILE ${depfile}                                                                                     # Specify dependency file
  )

  add_custom_target(${ModuleName}_bindings_generation DEPENDS ${wrap_cxx}) # We make the module depend on the bindings
  add_dependencies(${ModuleName} ${ModuleName}_bindings_generation)        # so that the generation happens before the compilation

endfunction()


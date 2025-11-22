macro(clair_c2py_generate_bindings ModuleName) 

  find_program(clair-c2py clair-c2py REQUIRED)                       # locate clair-c2py in the path or fail
  set(wrap_cxx "${CMAKE_CURRENT_SOURCE_DIR}/${ModuleName}.wrap.cxx") # Python bindings file
  set(depfile "${CMAKE_CURRENT_BINARY_DIR}/${ModuleName}.cpp.d")     # dependency file

  add_custom_command(
    OUTPUT ${wrap_cxx} ${depfile}                                                               # Generates the .wrap.cxx and dependency files
    COMMAND ${clair-c2py} -p ${PROJECT_BINARY_DIR} --generate-depfile ${depfile} ${ModuleName}.cpp  # -p path/to/compile/commands
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}                                               # Execute in source directory
    DEPFILE ${depfile}                                                                          # Specify dependency file
  )

  add_custom_target(${ModuleName}_bindings_generation DEPENDS ${wrap_cxx}) # We make the module depend on the bindings
  add_dependencies(${ModuleName} ${ModuleName}_bindings_generation)        # so that the generation happends before the compilation

endmacro()


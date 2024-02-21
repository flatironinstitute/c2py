add_subdirectory(cmake)

if(NOT IS_SUBPROJECT
  AND NOT CMAKE_INSTALL_PREFIX STREQUAL "/usr"
  AND NOT CMAKE_INSTALL_PREFIX STREQUAL "/usr/local"
)

  configure_file(c2py.modulefile.in c2py.modulefile @ONLY)
  configure_file(c2pyvars.sh.in c2pyvars.sh @ONLY)

  install(
    FILES
      ${CMAKE_CURRENT_BINARY_DIR}/c2py.modulefile
      ${CMAKE_CURRENT_BINARY_DIR}/c2pyvars.sh
    DESTINATION share/c2py
  )
 
  message(STATUS "*********************************************************************************")
  message(STATUS "* Custom install Location. Use:                                                  ")
  message(STATUS "*                                                                                ")
  message(STATUS "*   source ${CMAKE_INSTALL_PREFIX}/share/c2py/c2pyvars.sh  ")
  message(STATUS "*                                                                                ")
  message(STATUS "* to set up the environment variables                                            ")
  if(DEFINED ENV{MODULEPATH})
    message(STATUS "*                                                                          ")
    message(STATUS "* Consider copying ${CMAKE_CURRENT_BINARY_DIR}/c2py.modulefile  ")
    message(STATUS "*   into your environment module directories                               ")
  endif()
  message(STATUS "*********************************************************************************")

endif()

include(CheckCCompilerFlag)

macro(CHECK_LINKER_FLAG flag VARIABLE)
  if(NOT DEFINED "${VARIABLE}")
    if(NOT CMAKE_REQUIRED_QUIET)
      message(STATUS "Looking for ${flag} linker flag")
    endif()

    try_compile(
      ${VARIABLE}
      ${CMAKE_BINARY_DIR}
      SOURCES "int main(void) { return 0; }"
      LINK_OPTIONS ${_flag}
      OUTPUT_VARIABLE OUTPUT
    )

    if ("${OUTPUT}" MATCHES "warning.*ignored")
      set(${VARIABLE} 0)
    endif()

    if(${VARIABLE})
      if(NOT CMAKE_REQUIRED_QUIET)
        message(STATUS "Looking for ${flag} linker flag - found")
      endif()
      set(${VARIABLE} 1 CACHE INTERNAL "Have linker flag ${flag}")
      file(APPEND ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeOutput.log
        "Determining if the ${flag} linker flag is supported "
        "passed with the following output:\n"
        "${OUTPUT}\n\n")
    else()
      if(NOT CMAKE_REQUIRED_QUIET)
        message(STATUS "Looking for ${flag} linker flag - not found")
      endif()
      set(${VARIABLE} "" CACHE INTERNAL "Have linker flag ${flag}")
      file(APPEND ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeError.log
        "Determining if the ${flag} linker flag is supported "
        "failed with the following output:\n"
        "${OUTPUT}\n\n")
    endif()
  endif()
endmacro()

#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "glm" for configuration "Debug"
set_property(TARGET glm::glm APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(glm::glm PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/Debug/glm_static.lib"
  )

list(APPEND _cmake_import_check_targets glm )
list(APPEND _cmake_import_check_files_for_glm "${_IMPORT_PREFIX}/lib/Debug/glm_static.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
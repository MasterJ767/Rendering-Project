#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "physx" for configuration "Debug"
set_property(TARGET physx APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(physx PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/Debug/PhysX_64.lib"
  )
  
target_link_libraries(physx INTERFACE
  debug "${_IMPORT_PREFIX}/lib/Debug/PhysX_64.lib"
  debug "${_IMPORT_PREFIX}/lib/Debug/PhysXCharacterKinematic_static_64.lib"
  debug "${_IMPORT_PREFIX}/lib/Debug/PhysXCommon_64.lib"
  debug "${_IMPORT_PREFIX}/lib/Debug/PhysXCooking_64.lib"
  debug "${_IMPORT_PREFIX}/lib/Debug/PhysXExtensions_static_64.lib"
  debug "${_IMPORT_PREFIX}/lib/Debug/PhysXFoundation_64.lib"
  debug "${_IMPORT_PREFIX}/lib/Debug/PhysXPvdSDK_static_64.lib"
  debug "${_IMPORT_PREFIX}/lib/Debug/PhysXTask_static_64.lib"
  debug "${_IMPORT_PREFIX}/lib/Debug/PhysXVehicle_static_64.lib"
  debug "${_IMPORT_PREFIX}/lib/Debug/PhysXVehicle2_static_64.lib"
  debug "${_IMPORT_PREFIX}/lib/Debug/PVDRuntime_64.lib"
  )

list(APPEND _cmake_import_check_targets physx )
list(APPEND _cmake_import_check_files_for_physx "${_IMPORT_PREFIX}/lib/Debug/PhysX_64.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
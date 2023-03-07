#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "physx" for configuration "Release"
set_property(TARGET physx APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(physx PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/Release/PhysX_64.lib"
  )
  
target_link_libraries(physx INTERFACE
  optimized "${_IMPORT_PREFIX}/lib/Release/PhysX_64.lib"
  optimized "${_IMPORT_PREFIX}/lib/Release/PhysXCharacterKinematic_static_64.lib"
  optimized "${_IMPORT_PREFIX}/lib/Release/PhysXCommon_64.lib"
  optimized "${_IMPORT_PREFIX}/lib/Release/PhysXCooking_64.lib"
  optimized "${_IMPORT_PREFIX}/lib/Release/PhysXExtensions_static_64.lib"
  optimized "${_IMPORT_PREFIX}/lib/Release/PhysXFoundation_64.lib"
  optimized "${_IMPORT_PREFIX}/lib/Release/PhysXPvdSDK_static_64.lib"
  optimized "${_IMPORT_PREFIX}/lib/Release/PhysXTask_static_64.lib"
  optimized "${_IMPORT_PREFIX}/lib/Release/PhysXVehicle_static_64.lib"
  optimized "${_IMPORT_PREFIX}/lib/Release/PhysXVehicle2_static_64.lib"
  optimized "${_IMPORT_PREFIX}/lib/Release/PVDRuntime_64.lib"
  )

list(APPEND _cmake_import_check_targets physx )
list(APPEND _cmake_import_check_files_for_physx "${_IMPORT_PREFIX}/lib/Release/PhysX_64.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)

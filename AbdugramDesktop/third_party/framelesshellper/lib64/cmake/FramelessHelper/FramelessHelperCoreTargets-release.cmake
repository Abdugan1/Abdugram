#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "FramelessHelper::FramelessHelperCore" for configuration "Release"
set_property(TARGET FramelessHelper::FramelessHelperCore APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(FramelessHelper::FramelessHelperCore PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib64/libFramelessHelperCore.so.2.4.2"
  IMPORTED_SONAME_RELEASE "libFramelessHelperCore.so.2"
  )

list(APPEND _IMPORT_CHECK_TARGETS FramelessHelper::FramelessHelperCore )
list(APPEND _IMPORT_CHECK_FILES_FOR_FramelessHelper::FramelessHelperCore "${_IMPORT_PREFIX}/lib64/libFramelessHelperCore.so.2.4.2" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)

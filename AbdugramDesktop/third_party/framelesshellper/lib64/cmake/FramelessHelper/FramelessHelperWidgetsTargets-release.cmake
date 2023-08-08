#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "FramelessHelper::FramelessHelperWidgets" for configuration "Release"
set_property(TARGET FramelessHelper::FramelessHelperWidgets APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(FramelessHelper::FramelessHelperWidgets PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "Qt5::Widgets"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib64/libFramelessHelperWidgets.so.2.4.2"
  IMPORTED_SONAME_RELEASE "libFramelessHelperWidgets.so.2"
  )

list(APPEND _IMPORT_CHECK_TARGETS FramelessHelper::FramelessHelperWidgets )
list(APPEND _IMPORT_CHECK_FILES_FOR_FramelessHelper::FramelessHelperWidgets "${_IMPORT_PREFIX}/lib64/libFramelessHelperWidgets.so.2.4.2" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)

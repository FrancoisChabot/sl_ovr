cmake_minimum_required(VERSION 3.9)

project(sl_ovr)

# Determine if sl_ovr is built as a subproject (using add_subdirectory)
# or if it is the master project.
set(MASTER_PROJECT OFF)
if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(MASTER_PROJECT ON)
endif ()

option(SL_OVR_BUILD_EXAMPLES "Build examples" ${MASTER_PROJECT})

SET(SL_OVR_SRC
  src/sl_ovr/errors.cpp
  src/sl_ovr/find_client_lib.cpp
  src/sl_ovr/ivrclientcore.h
  src/sl_ovr/ovr_context.cpp
  src/sl_ovr/ovr_system.cpp
  src/sl_ovr/shared_lib_utils.cpp
)

SET(SL_OVR_HEADERS
  include/sl_ovr/detail/interface_infos.h
  include/sl_ovr/detail/shared_lib_utils.h
  include/sl_ovr/errors.h
  include/sl_ovr/openvr_api.h
  include/sl_ovr/sl_ovr
)

add_library( sl_ovr ${SL_OVR_SRC} ${SL_OVR_HEADERS})
add_library(sl_ovr::sl_ovr ALIAS sl_ovr)

target_compile_features(sl_ovr PUBLIC cxx_std_11)

target_include_directories(sl_ovr 
PRIVATE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include>
)

install(TARGETS sl_ovr
  EXPORT   sl_ovrTargets
  ARCHIVE  DESTINATION lib
  LIBRARY  DESTINATION lib
  RUNTIME  DESTINATION bin
)

#install cmake export
install(EXPORT sl_ovrTargets DESTINATION lib/cmake/sl_ovr)

configure_file(cmake/sl_ovr-config.cmake.in
  "${PROJECT_BINARY_DIR}/sl_ovr-config.cmake" @ONLY)

#install headers
install(DIRECTORY include/sl_ovr DESTINATION include)

install(FILES
  "${PROJECT_BINARY_DIR}/sl_ovr-config.cmake"
  DESTINATION lib/cmake/sl_ovr)

add_subdirectory(examples)
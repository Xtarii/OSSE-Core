#
# OSSE - Open Source Search Engine
#
cmake_minimum_required(VERSION 4.0)
project(osse)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



# CORE Files ( OSSE Library files )
add_library(osse STATIC src/core.cpp
    src/URI/URI.cpp
    src/config/Config.cpp
)
target_link_libraries(osse PRIVATE curl)



# CORE Headers
include_directories(headers)
target_include_directories(osse PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/headers>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/OSSE>
)



# Github Installation Support
include(GNUInstallDirs)

install(TARGETS osse EXPORT OSSE)
install(DIRECTORY headers/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/OSSE)
install(EXPORT OSSE
    FILE OSSE.cmake
    NAMESPACE OSSE::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/osse
)



# Installation Support
include(CMakePackageConfigHelpers)

configure_package_config_file(
    "Config.cmake.in"
    "OSSEConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/osse
    PATH_VARS CMAKE_INSTALL_LIBDIR
)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/OSSEConfigVersion.cmake
    VERSION 1.0.0
    COMPATIBILITY AnyNewerVersion
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/OSSEConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/OSSEConfigVersion.cmake"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/osse"
)





# Test
add_executable(test .test/main.cpp)
target_link_libraries(test PRIVATE osse)

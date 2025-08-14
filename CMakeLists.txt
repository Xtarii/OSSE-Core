#
# OSSE - Open Source Search Engine
#
cmake_minimum_required(VERSION 4.0)
project(osse)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



# CORE Files ( OSSE Library files )
add_library(osse SHARED src/core.cpp
    # OSSE Components
    src/URI/URI.cpp
    src/robots/Robots.cpp
    src/queue/Queue.cpp

    src/database/Database.cpp
    src/database/simple/SimpleDatabase.cpp

    src/error/Error.cpp

    # Crawlers
    src/crawler/Manager.cpp
    src/crawler/worker/Worker.cpp

    # Algorithms
    src/algorithm/Algorithm.cpp

    # OSSE Configuration
    src/config/Config.cpp
    src/config/Defaults.cpp

    # HTML Handling
    src/HTML/HTML.cpp
)

find_package(LibXml2 REQUIRED)
find_package(CURL REQUIRED)

target_link_libraries(osse PRIVATE
    CURL::libcurl
    LibXml2::LibXml2
)



# Gets CMAKE installation path
include(GNUInstallDirs)

# CORE Headers
include_directories(headers)
target_include_directories(osse
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/headers>
    $<INSTALL_INTERFACE:include/OSSE>
)

# Installation Support
install(TARGETS osse
    EXPORT OSSETargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/OSSE
)
install(DIRECTORY headers/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/OSSE)
install(EXPORT OSSETargets
    FILE OSSETargets.cmake
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
    VERSION 0.2
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

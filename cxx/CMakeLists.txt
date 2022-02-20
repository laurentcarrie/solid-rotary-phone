cmake_minimum_required(VERSION 3.21)
project(solid_rotary_phone)

set(CMAKE_CXX_STANDARD 17)
set(YAMLCPP_STATIC_LIBRARY false)

file(GLOB LIBRARIES "/opt/homebrew/Cellar/yaml-cpp/0.7.0/lib/*.dylib")

if(YAMLCPP_STATIC_LIBRARY)
    set(YAMLCPP_STATIC libyaml-cpp.a)
endif()

# find the yaml-cpp include directory
find_path(YAMLCPP_INCLUDE_DIR yaml-cpp/yaml.h
        PATH_SUFFIXES include
        PATHS
        /opt/homebrew/Cellar/yaml-cpp/0.7.0/include/
        ~/Library/Frameworks/yaml-cpp/include/
        /Library/Frameworks/yaml-cpp/include/
        /usr/local/include/
        /usr/include/
        /sw/yaml-cpp/         # Fink
        /opt/local/yaml-cpp/  # DarwinPorts
        /opt/csw/yaml-cpp/    # Blastwave
        /opt/yaml-cpp/
        ${YAMLCPP_DIR}/include/)

# find the yaml-cpp library
find_library(YAMLCPP_LIBRARY
        NAMES  yaml-cpp
        PATH_SUFFIXES lib64 lib dylib
        PATHS ~/Library/Frameworks
        /Library/Frameworks
        /usr/local
        /usr
        /sw
        /opt/local
        /opt/csw
        /opt
        /opt/homebrew/Cellar/yaml-cpp/0.7.0/lib
        ${YAMLCPP_DIR}/lib)

include_directories(/opt/homebrew/Cellar/yaml-cpp/0.7.0/include/)
include_directories(/opt/homebrew/Cellar/yaml-cpp/0.7.0/lib/)

# handle the QUIETLY and REQUIRED arguments and set YAMLCPP_FOUND to TRUE if all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(YAMLCPP DEFAULT_MSG YAMLCPP_INCLUDE_DIR YAMLCPP_LIBRARY)
#mark_as_advanced(YAMLCPP_INCLUDE_DIR YAMLCPP_LIBRARY)
add_executable(solid_rotary_phone main.cpp parse.cpp parse.h to_html.cpp to_html.h config.cpp config.h)
#target_link_libraries(solid_rotary_phone yaml-cpp)
target_link_libraries(solid_rotary_phone ${LIBRARIES})
#target_link_directories(solid_rotary_phone /opt/homebrew/Cellar/yaml-cpp/0.7.0/lib/)

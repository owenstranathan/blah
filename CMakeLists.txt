cmake_minimum_required(VERSION 3.0)
project(blah)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)

set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/SFML/cmake-modules/")
find_library (SFML REQUIRED sfml-window)

link_directories(/usr/local/lib/)
if(NOT SFML)
#   message(FATAL_ERROR "sfml library not found")
endif()

add_subdirectory(src)
target_compile_definitions(blahSources PRIVATE SFML_STATIC)
include_directories(${SFML_INCLUDE_DIR})

add_executable(blah src/main.cpp)

target_compile_definitions(blah PRIVATE SFML_STATIC)
target_link_libraries(blah blahSources sfml-window sfml-system sfml-graphics)

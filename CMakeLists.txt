cmake_minimum_required(VERSION 3.16)
project(sphere-rendering LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SFML REQUIRED IMPORTED_TARGET sfml-graphics sfml-window sfml-system)

set(SOURCE_DIR source)
set(INCLUDE_DIR include)

file( GLOB_RECURSE SOURCE_FILES ${SOURCE_DIR}/*.cpp
								${SOURCE_DIR}/**/*.cpp )

add_executable(chemical-reaction ${SOURCE_FILES})

target_include_directories(chemical-reaction PRIVATE ${INCLUDE_DIR})

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}")

target_link_libraries(chemical-reaction PRIVATE PkgConfig::SFML)

find_package(OpenMP REQUIRED)
target_link_libraries(chemical-reaction PRIVATE OpenMP::OpenMP_CXX)

target_include_directories(chemical-reaction PRIVATE src)

install(TARGETS chemical-reaction DESTINATION bin)

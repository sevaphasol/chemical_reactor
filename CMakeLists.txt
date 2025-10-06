cmake_minimum_required( VERSION 3.16 )
project( reactor LANGUAGES CXX )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

file( GLOB_RECURSE REACTOR_SOURCES CONFIGURE_DEPENDS
	${CMAKE_CURRENT_SOURCE_DIR}/source/reactor/*.cpp
)

add_executable( reactor ${REACTOR_SOURCES} )
target_include_directories( reactor PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_subdirectory( gfxlib )
target_link_libraries(reactor PRIVATE gfx)

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}")
install(TARGETS reactor DESTINATION bin)

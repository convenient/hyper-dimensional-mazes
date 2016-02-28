cmake_minimum_required(VERSION 3.3)
project(mazes_for_programmers)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#Output directory for files
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib )

#Configure for test suite
set( GOOGLE_TEST_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests/lib/googletest-release-1.7.0)
set( BASE_PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
add_subdirectory(tests)

#Define executables
## Binary
add_executable(binary src/binary.cpp)

## OpenGL
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

add_executable(opengl src/opengl.cpp)

target_link_libraries(opengl ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )

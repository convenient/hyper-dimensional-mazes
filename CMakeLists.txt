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
add_executable(binary_2d src/binary2d.cpp)
add_executable(binary_3d src/binary3d.cpp)
add_executable(binary_nd src/binary.cpp)

#Sidewinder
add_executable(sidewinder_2d src/sidewinder2d.cpp)
add_executable(sidewinder_3d src/sidewinder3d.cpp)
add_executable(sidewinder_nd src/sidewinder.cpp)

#Aldous Broder
add_executable(aldous_broder_2d src/aldousBroder2d.cpp)
add_executable(aldous_broder_3d src/aldousBroder3d.cpp)
add_executable(aldous_broder_nd src/aldousBroder.cpp)

#Wilsons
add_executable(wilsons_2d src/wilsons2d.cpp)
add_executable(wilsons_3d src/wilsons3d.cpp)
add_executable(wilsons_nd src/wilsons.cpp)

#Recursive backtracker
add_executable(recursive_backtracker_2d src/recursivebacktracker2d.cpp)
add_executable(recursive_backtracker_3d src/recursivebacktracker3d.cpp)
add_executable(recursive_backtracker_nd src/recursivebacktracker.cpp)

## OpenGL
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(sidewinder_2d ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} pthread)
target_link_libraries(sidewinder_3d ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} pthread)
target_link_libraries(sidewinder_nd pthread)
target_link_libraries(binary_2d ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} pthread)
target_link_libraries(binary_3d ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} pthread)
target_link_libraries(binary_nd pthread)
target_link_libraries(aldous_broder_2d ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} pthread)
target_link_libraries(aldous_broder_3d ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} pthread)
target_link_libraries(aldous_broder_nd pthread)
target_link_libraries(wilsons_2d ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} pthread)
target_link_libraries(wilsons_3d ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} pthread)
target_link_libraries(wilsons_nd pthread)
target_link_libraries(recursive_backtracker_2d ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} pthread)
target_link_libraries(recursive_backtracker_3d ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} pthread)
target_link_libraries(recursive_backtracker_nd pthread)

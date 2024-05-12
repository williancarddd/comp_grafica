cmake_minimum_required(VERSION 3.10)
project(SolarSystem)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIR})

add_executable(SolarSystem main.cpp SolarSystem.cpp)

target_link_libraries(SolarSystem ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})

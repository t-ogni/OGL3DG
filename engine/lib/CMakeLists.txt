cmake_minimum_required(VERSION 3.0)
find_package(OpenGL REQUIRED)
project(deps)

add_subdirectory(glad)
add_subdirectory(soil)

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(glfw)
include_directories(glfw/include/)
include_directories(glfw/deps/)

cmake_minimum_required(VERSION 3.4)
project(deps)
add_library(deps INTERFACE)

if(POLICY CMP0072)
    cmake_policy(SET CMP0072 OLD)
endif()

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(glm_DIR ./glm/cmake/glm)

find_package(OpenGL REQUIRED)
#find_package(GLUT REQUIRED)
find_package(glm REQUIRED)
add_subdirectory(glad)
add_subdirectory(soil)
add_subdirectory(glfw)

target_include_directories(deps INTERFACE glfw/include/)
target_include_directories(deps INTERFACE glfw/deps/)
target_include_directories(deps INTERFACE ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS})
target_link_libraries(deps INTERFACE
        ${OPENGL_LIBRARIES} ${GLUT_LIBRARY}
        glfw ${GLFW_LIBRARIES}
        glm::glm
        soil
        glad
)

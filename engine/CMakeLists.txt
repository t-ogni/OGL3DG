cmake_minimum_required(VERSION 3.1)
project(PhonEngine VERSION 0.1)


# Include Libraries -----------------------------------------------------------
add_subdirectory(lib) # to include external libs

set(glm_DIR lib/glm/cmake/glm)
find_package(glm REQUIRED)

file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/source/*.cpp" )

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC source)

target_link_libraries(${PROJECT_NAME}
        ${OPENGL_LIBRARY}
        glfw ${GLFW_LIBRARIES}
        soil
        glad
        glm::glm
)

file(COPY ${PROJECT_SOURCE_DIR}/runtime DESTINATION ${EXECUTABLE_OUTPUT_PATH})
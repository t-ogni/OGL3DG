cmake_minimum_required(VERSION 3.1)

# Project Information ---------------------------------------------------------
project(PhonEngine VERSION 0.1)


# Include Libraries -----------------------------------------------------------
add_subdirectory(lib) # to include external libs

include_directories(include)
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp" )

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_link_libraries(${PROJECT_NAME}
        ${OPENGL_LIBRARY}
        glfw ${GLFW_LIBRARIES}
        soil
        glad
        glm::glm
)

file(COPY ${PROJECT_SOURCE_DIR}/shaders DESTINATION ${EXECUTABLE_OUTPUT_PATH})
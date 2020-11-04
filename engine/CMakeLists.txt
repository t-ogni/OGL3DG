cmake_minimum_required(VERSION 3.1)

# Project Information ---------------------------------------------------------
project(PhonEngine VERSION 0.1)

# Get Info About Compiler -----------------------------------------------------
IF(CMAKE_SIZEOF_VOID_P EQUAL 8)  #64 bit
    message(STATUS "Running on 64bit platform. Proceeding...")
ELSE()
    message(STATUS "Running on 32bit platform. Proceeding...")
ENDIF()

set(PROJECT_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)
file(COPY ${PROJECT_SOURCE_DIR}/shaders DESTINATION ${EXECUTABLE_OUTPUT_PATH})


# Include Libraries -----------------------------------------------------------
add_subdirectory(${PROJECT_LIB_DIR}) # to include external libs

include_directories(include)
file(GLOB SOURCES
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_link_libraries(${PROJECT_NAME}
        ${OPENGL_LIBRARY}
        glfw ${GLFW_LIBRARIES}
        glad
        glm::glm
        )
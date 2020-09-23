cmake_minimum_required(VERSION 3.1)

# Project Information ---------------------------------------------------------
project(OGL3DG VERSION 0.1)
set(PROJ_EXE_NAME "${PROJECT_NAME}.ver${PROJECT_VERSION}")
message("Project & Version: " ${PROJECT_NAME} " " ${PROJECT_VERSION} )


# Get Info About Compiler -----------------------------------------------------
IF(CMAKE_SIZEOF_VOID_P EQUAL 8)  #64 bit
    message(STATUS "Running on 64bit platform. Proceeding...")
ELSE()
    message(STATUS "Running on 32bit platform. Proceeding...")
ENDIF()



# Configure Flags -------------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -static-libgcc -static-libstdc++ -static")


# Configure Source & Binary Directories ---------------------------------------
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build) #builded exe will be added to that path
set(PROJECT_LIB_DIR ${PROJECT_SOURCE_DIR}/lib )

file( COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders DESTINATION ${EXECUTABLE_OUTPUT_PATH})
file( COPY ${CMAKE_CURRENT_SOURCE_DIR}/common DESTINATION ${EXECUTABLE_OUTPUT_PATH})



# Include Libraries -----------------------------------------------------------
find_package(OpenGL REQUIRED)

add_subdirectory(${PROJECT_LIB_DIR}) # to include external libs

include_directories(include) # headers

file(GLOB SOURCES
        "${PROJECT_SOURCE_DIR}/src/*.c"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/include/*.hpp"
)

add_executable(
        ${PROJ_EXE_NAME}
        ${SOURCES}
)

add_custom_command(
        TARGET ${PROJ_EXE_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders
        ${EXECUTABLE_OUTPUT_PATH})

add_custom_command(
        TARGET ${PROJ_EXE_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/common
        ${EXECUTABLE_OUTPUT_PATH})


target_link_libraries(
        ${PROJ_EXE_NAME}
        -static gcc stdc++ winpthread -dynamic
        ${OPENGL_LIBRARY}
        glfw ${GLFW_LIBRARIES}
        glad
        glm::glm
)


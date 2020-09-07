cmake_minimum_required(VERSION 3.1)

# Project Information ---------------------------------------------------------
project(OGL3DG VERSION 0.1)
set(PROJ_EXE_NAME ${PROJECT_NAME}-ver${PROJECT_VERSION})
message("Project & Version: " ${PROJECT_NAME} " " ${PROJECT_VERSION} )

IF(CMAKE_SIZEOF_VOID_P EQUAL 8)  #64 bit
    message(STATUS "Running on 64bit platform. Proceeding...")
ELSE()
    message(STATUS "Running on 32bit platform. Proceeding...")
ENDIF()

# Configure Flags -------------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Waddress -Warray-bounds=1 -Wint-in-bool-context" )
# -Wall - включает базовые предупреждения
# -Waddress - некорректное использование адресов
# -Warray-bounds=1 - выход за пределы массива
# -Wint-in-bool-context - использование целых чисел там, где ожидаются булевы выражения

# Configure Source & Binary Directories ---------------------------------------
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build) #builded exe will be added to that path
set(PROJECT_LIB_DIR ${PROJECT_SOURCE_DIR}/lib )



# Include Libraries -----------------------------------------------------------
find_package(OpenGL REQUIRED)

add_subdirectory(${PROJECT_LIB_DIR}) # to include external libs

include_directories(include) # headers

set(SOURCES
        ${PROJECT_SOURCE_DIR}/src/main.cpp
        src/Globals.cpp
)

add_executable(
        ${PROJ_EXE_NAME}
        ${SOURCES}
)
target_link_libraries(
        ${PROJ_EXE_NAME}
        ${OPENGL_LIBRARY}
        glfw ${GLFW_LIBRARIES}
        glad
)

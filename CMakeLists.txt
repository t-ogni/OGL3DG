cmake_minimum_required(VERSION 3.1)
project(OGL3DG VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)
set(PROJECT_LIB_DIR ${PROJECT_SOURCE_DIR}/lib )

include_directories(include)

set(SOURCES
        src/main.cpp
        src/foo.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

cmake_minimum_required(VERSION 3.4)
project(PhonEngine VERSION 0.1)  # any title ideas?

## Include Libraries -----------------------------------------------------------
add_subdirectory(lib) # to include external libs

file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/source/*.cpp" )  # recurse search cpp's

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC source)
target_link_libraries(${PROJECT_NAME} deps)

if(COPY_RUNTIME)  # костыли
    file(COPY ${PROJECT_SOURCE_DIR}/runtime DESTINATION ${EXECUTABLE_OUTPUT_PATH})
endif()

cmake_minimum_required(VERSION 3.1)
project(OGL3DG VERSION 0.1)
message("Project & Version: ${PROJECT_NAME} ${PROJECT_VERSION}")
set(PROJ_EXE_NAME "${PROJECT_NAME}_v${PROJECT_VERSION}_x${BITSYS}" )

# obtaining information about the bit depth
math(EXPR BITSYS "${CMAKE_SIZEOF_VOID_P}*8")
message(STATUS "Running on ${BITSYS}bit platform...")

# Configure Flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")

# path to create the final program
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/RELEASE)
file(COPY ${PROJECT_SOURCE_DIR}/res DESTINATION ${EXECUTABLE_OUTPUT_PATH})

# link & build
add_subdirectory(engine)
add_executable(${PROJ_EXE_NAME} main.cpp)
target_link_libraries(${PROJ_EXE_NAME} PhonEngine)

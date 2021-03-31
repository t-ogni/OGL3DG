cmake_minimum_required(VERSION 3.1)
project(OGL3DG VERSION 0.1)
message("Project & Version: ${PROJECT_NAME} ${PROJECT_VERSION}")

# obtaining information about the bit depth
math(EXPR BITSYS "${CMAKE_SIZEOF_VOID_P}*8")
message(STATUS "Running on ${BITSYS}-bit platform...")

# output executable name
set(PROJ_EXE_NAME "${PROJECT_NAME}_v${PROJECT_VERSION}_x${BITSYS}" )

# Configure Flags
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")

# path to create the final program
set(COPY_RUNTIME True)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)

#file(GLOB OBJs ${PROJECT_SOURCE_DIR}/res/*.obj)
#file(GLOB MTLs ${PROJECT_SOURCE_DIR}/res/*.mtl)

file(COPY ${PROJECT_SOURCE_DIR}/res DESTINATION ${EXECUTABLE_OUTPUT_PATH})

# link & build
add_subdirectory(engine)
add_executable(${PROJ_EXE_NAME} OGL3DG/main.cpp)
target_link_libraries(${PROJ_EXE_NAME} PhonEngine)


add_executable(unitsTest Unit_test.cpp)
target_link_libraries(unitsTest PhonEngine)


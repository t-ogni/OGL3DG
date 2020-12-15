cmake_minimum_required(VERSION 3.1)
project(OGL3DG VERSION 0.1)
message("Project & Version: ${PROJECT_NAME} ${PROJECT_VERSION}")

# Configure Flags -------------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++ -static")
set(PROJ_EXE_NAME "${PROJECT_NAME}.ver${PROJECT_VERSION}")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build) #builded exe will be added to that path
file(COPY ${PROJECT_SOURCE_DIR}/res DESTINATION ${EXECUTABLE_OUTPUT_PATH})

IF (CMAKE_SIZEOF_VOID_P EQUAL 8)  #64 OR 32 bit compiler
    message(STATUS "Running on 64bit platform. Proceeding...")
ELSE ()
    message(STATUS "Running on 32bit platform. Proceeding...")
ENDIF ()

# build -----------------------------------------------------------------------
add_subdirectory(engine)
message("PhonEngine Version: ${PhonEngine_VERSION}")

add_executable(
        ${PROJ_EXE_NAME}
        main.cpp
)



target_link_libraries(
        ${PROJ_EXE_NAME}
        -static gcc stdc++ winpthread -dynamic
        PhonEngine
)

add_executable(
        tests
        Unit_test.cpp
)

target_link_libraries(
        tests
        -static gcc stdc++ winpthread -dynamic
        PhonEngine
)
cmake_minimum_required(VERSION 3.1)
project(OGL3DG VERSION 0.1)
message("Project & Version: ${PROJECT_NAME} ${PROJECT_VERSION}")

# Configure Flags -------------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++ -static")
set(PROJ_EXE_NAME "${PROJECT_NAME}.ver${PROJECT_VERSION}")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build) #builded exe will be added to that path

# build -----------------------------------------------------------------------
add_subdirectory(engine)
message("PhorEngine Version: ${PhorEngine_VERSION}")

add_executable(
        ${PROJ_EXE_NAME}
        main.cpp
)
target_link_libraries(
        ${PROJ_EXE_NAME}
        -static gcc stdc++ winpthread -dynamic

        PhonEngine
)


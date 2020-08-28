cmake_minimum_required(VERSION 3.1)

project(GLAD LANGUAGES C)

add_library(
        glad
        src/glad.c
        include/glad/glad.h
        include/KHR/khrplatform.h
)

target_include_directories(
        glad
        PUBLIC
        include/
)

target_link_libraries(glad ${CMAKE_DL_LIBS})
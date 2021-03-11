cmake_minimum_required(VERSION 2.6)

ADD_LIBRARY( soil STATIC
  src/image_helper.c
  src/stb_image_aug.c
  src/image_DXT.c
  src/SOIL.c
  )

target_include_directories(soil PUBLIC inc)

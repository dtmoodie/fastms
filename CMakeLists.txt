cmake_minimum_required(VERSION 3.0)

find_package(OpenCV REQUIRED core)

find_package(CUDA REQUIRED)

FILE(GLOB_RECURSE src "src/libfastms/*.cpp")
FILE(GLOB_RECURSE hdr "src/libfastms/*.h")
FILE(GLOB_RECURSE knlhdr "src/libfastms/*.cuh")
FILE(GLOB_RECURSE knl "src/libfastms/*.cu")
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})
INCLUDE_DIRECTORIES("src/libfastms")
cuda_add_library(fastms ${src} ${hdr} ${knlhdr} ${knl})


find_package(OpenCV QUIET COMPONENTS core)
set_target_properties(${OpenCV_LIBS} PROPERTIES MAP_IMPORTED_CONFIG_RELWITHDEBINFO RELEASE)
CMAKE_POLICY(SET CMP0020 NEW)
find_package(CUDA REQUIRED)
SET(CMAKE_DEBUG_POSTFIX "d")
FILE(GLOB_RECURSE src "src/libfastms/*.cpp")
FILE(GLOB_RECURSE hdr "src/libfastms/*.h")
FILE(GLOB_RECURSE knlhdr "src/libfastms/*.cuh")
FILE(GLOB_RECURSE knl "src/libfastms/*.cu")
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})
INCLUDE_DIRECTORIES("src/libfastms")
IF(WIN32)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /FS")
ELSE(WIN32)
#SET(CUDA_NVCC_FLAGS "-ccbin g++;-O2;-std=c++11;${CUDA_NVCC_FLAGS}")
ENDIF(WIN32)
if(RCC_VERBOSE_CONFIG)
message(STATUS
" ============= fastMS ==========
        Headers: ${hdr}
        Src: ${src}
        Kernel Headers: ${knlhdr}
        Kernel: ${knl}
")
endif()
cuda_add_library(fastms SHARED ${src} ${hdr} ${knlhdr} ${knl})
TARGET_LINK_LIBRARIES(fastms ${CUDA_CUBLAS_LIBRARIES} ${OpenCV_LIBRARIES})
install(TARGETS fastms DESTINATION lib) 
install(FILES ${hdr} DESTINATION include)

set(fastms_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/src PARENT_SCOPE)

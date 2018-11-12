cmake_minimum_required (VERSION 2.6)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

project (MOG)

file( GLOB FONTES "src/*.cpp" )
include_directories( include )

add_executable(MOG main.cpp ${FONTES})

find_package (OpenCV REQUIRED)
include_directories (${OpenCV_INCLUDE_DIRS})

target_link_libraries (MOG ${OpenCV_LIBS})

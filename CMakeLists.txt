cmake_minimum_required(VERSION 3.13) 

project(learning-opengl)            

set(OUTPUT_BINARY main)

file(GLOB_RECURSE sources src/*.cpp src/*.c src/headers/*.h src/headers/*.hpp)
# file(GLOB_RECURSE sources_test src/test/*.cpp)
# file(GLOB_RECURSE data resources/*)

set(CMAKE_OUTPUT_DIR ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_OUTPUT_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenGL REQUIRED)

include_directories(${CMAKE_INCLUDE_DIR})
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c17 -g -Wall -Wextra -Wfloat-conversion -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -g -Wall -Wextra -Wfloat-conversion -pedantic")

add_executable(${OUTPUT_BINARY} ${sources})

if (APPLE) 
	target_link_libraries(${OUTPUT_BINARY} glfw)
else ()
	find_package(glfw REQUIRED)
	target_link_libraries(${OUTPUT_BINARY} OpenGL glfw)
endif()

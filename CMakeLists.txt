cmake_minimum_required(VERSION 3.13) 

project(learning-opengl)            

set(OUTPUT_BINARY main)

file(GLOB_RECURSE sources src/*.cpp src/*.c src/headers/*.h src/headers/*.hpp)
# file(GLOB_RECURSE sources_test src/test/*.cpp)
# file(GLOB_RECURSE data resources/*)

set(CMAKE_OUTPUT_DIR ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_OUTPUT_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c17 -g -Wall -Wextra -Wfloat-conversion -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -g -Wall -Wextra -Wfloat-conversion -pedantic")
set(GLFW_LIB_NAME "glfw")
set(GLFW_LIB_VERSION "3.4")
set(GLFW_LIB_SEARCH_NAME "${GLFW_LIB_NAME}.${GLFW_LIB_VERSION}")

find_package(OpenGL REQUIRED)
find_library(GLFW_FOUND ${GLFW_LIB_SEARCH_NAME} REQUIRED)
message("-- Found ${GLFW_LIB_SEARCH_NAME} in ${GLFW_FOUND}")

include_directories(${CMAKE_INCLUDE_DIR})
add_executable(${OUTPUT_BINARY} ${sources})
target_link_libraries(${OUTPUT_BINARY} PRIVATE ${GLFW_LIB_NAME})
if (NOT APPLE) 
	target_link_libraries(${OUTPUT_BINARY} PRIVATE OpenGL)
endif()

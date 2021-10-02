cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(SnakeGame)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")



set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} src)
file(GLOB SOURCES "src/*.cpp")

add_executable(SnakeGame ${SOURCES})
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)

target_link_libraries(SnakeGame ${SDL2_LIBRARIES})

if(CMAKE_BUILD_TYPE MATCHES Debug)
message(STATUS "Seting debug options")    
add_compile_definitions(DEBUG_BUILD)
endif()
cmake_minimum_required(VERSION 3.16)
project(NICNAC16_Simulator CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
    cpp_include
    cpp_src
    generated_cpp 
)

file(GLOB SOURCES "cpp_src/*.cpp")
file(GLOB GENERATED_SOURCES "generated_cpp/*.cpp")

add_executable(nicnac16_sim ${SOURCES} ${GENERATED_SOURCES})

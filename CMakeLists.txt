cmake_minimum_required(VERSION 3.16)
project(NICNAC16_Simulator CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
    cpp_include
    cpp_src
    generated_cpp 
)

file(GLOB SIM_SOURCES "cpp_src/processor.cpp")
file(GLOB GENERATED_SOURCES "generated_cpp/*.cpp")

add_library(nicnac_lib ${SIM_SOURCES} ${GENERATED_SOURCES})

add_executable(nicnac16_sim cpp_src/main.cpp)
target_link_libraries(nicnac16_sim PRIVATE nicnac_lib)

enable_testing()
add_subdirectory(tests)

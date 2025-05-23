add_executable(sim_tests simulator_basic.cpp)
target_include_directories(sim_tests PRIVATE ${PROJECT_SOURCE_DIR}/cpp_include ${PROJECT_SOURCE_DIR}/generated_cpp ${PROJECT_SOURCE_DIR}/tests)
target_link_libraries(sim_tests PRIVATE nicnac_lib)
add_test(NAME simulator_basic COMMAND sim_tests)

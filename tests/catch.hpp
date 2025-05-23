#pragma once
#include <functional>
#include <vector>
#include <string>
#include <iostream>
struct TestCase { std::string name; std::function<void()> func; };
inline std::vector<TestCase>& getRegistry() { static std::vector<TestCase> r; return r; }
struct Registrar { Registrar(const std::string& n,std::function<void()> f){ getRegistry().push_back({n,f}); } };
#define TEST_CASE(name) static void test_##name(); static Registrar registrar_##name(#name,test_##name); static void test_##name()
#define REQUIRE(cond) do { if(!(cond)){ std::cerr<<"Requirement failed: "#cond" at "<<__FILE__<<":"<<__LINE__<<std::endl; std::terminate(); } } while(0)
inline int run_tests(){int failed=0;for(auto&tc:getRegistry()){try{tc.func();std::cout<<"[OK] "<<tc.name<<std::endl;}catch(...){std::cout<<"[FAIL] "<<tc.name<<std::endl;failed++;}}std::cout<<getRegistry().size()-failed<<"/"<<getRegistry().size()<<" tests passed."<<std::endl;return failed;}

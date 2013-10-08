cmake_minimum_required(VERSION 2.8)
project(cxx11music CXX)
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
# FindBoost does not allow to specify Boost headers as required and components
# (libraries) as optional.  Work around this by invoking it twice.
find_package(Boost QUIET COMPONENTS unit_test_framework)
add_definitions(-std=c++11)
add_executable(${CMAKE_PROJECT_NAME}test test.cpp)
if(Boost_UNIT_TEST_FRAMEWORK_FOUND)
  set_target_properties(${CMAKE_PROJECT_NAME}test
                        PROPERTIES COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK)
  target_link_libraries(${CMAKE_PROJECT_NAME}test ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
else(Boost_UNIT_TEST_FRAMEWORK_FOUND)
  message(STATUS "Boost unit test framework library not available")
endif(Boost_UNIT_TEST_FRAMEWORK_FOUND)

enable_testing()
file(STRINGS test.cpp ${CMAKE_PROJECT_NAME}_BOOST_AUTO_TEST_CASE_matches
     REGEX "^BOOST_AUTO_TEST_CASE\\([a-zA-Z][a-zA-Z0-9_]*\\)")
foreach(match ${${CMAKE_PROJECT_NAME}_BOOST_AUTO_TEST_CASE_matches})
  string(REGEX REPLACE "^BOOST_AUTO_TEST_CASE\\(([a-zA-Z][a-zA-Z0-9_]*)\\).*$" "\\1"
         test_name ${match})
  add_test(NAME ${test_name}
           COMMAND ${CMAKE_PROJECT_NAME}test --run_test=${test_name})
endforeach(match)

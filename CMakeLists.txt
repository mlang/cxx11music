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
  message("-- Boost unit test framework libraries not available")
endif(Boost_UNIT_TEST_FRAMEWORK_FOUND)
file(STRINGS test.cpp ${CMAKE_PROJECT_NAME}_BOOST_AUTO_TEST_CASES
     REGEX "^BOOST_AUTO_TEST_CASE")
string(REGEX REPLACE "^BOOST_AUTO_TEST_CASE\\((.*)\\).*$" "\\1"
       ${CMAKE_PROJECT_NAME}_TEST_NAMES
       ${${CMAKE_PROJECT_NAME}_BOOST_AUTO_TEST_CASES})
enable_testing()
foreach(test_name ${${CMAKE_PROJECT_NAME}_TEST_NAMES})
  add_test(NAME ${test_name}
           COMMAND ${CMAKE_PROJECT_NAME}test --run_test=${test_name})
endforeach(test_name)

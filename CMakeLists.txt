cmake_minimum_required(VERSION 3.8)
project(graph)

enable_testing()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(GoogleTest)

add_subdirectory(googletest)

set(FooTestArgs )

include_directories(googletest/googletest googletest/googletest/include)

add_executable(${PROJECT_NAME} main.cpp algo/example.cpp test/example.cpp )

target_link_libraries(${PROJECT_NAME} gtest gtest_main)
gtest_add_tests(${PROJECT_NAME} "${FooTestArgs}" AUTO)

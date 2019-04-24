cmake_minimum_required(VERSION 3.8)
project(graph)

enable_testing()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(UNIX)
    set(FooTestArgs )

    include(GoogleTest)
    add_subdirectory(googletest)
    include_directories(googletest/googletest googletest/googletest/include)

    add_executable(${PROJECT_NAME}_test test/test_direction.cpp)
    gtest_add_tests(${PROJECT_NAME}_test "${FooTestArgs}" AUTO)
    target_link_libraries(${PROJECT_NAME}_test gtest gtest_main)
endif()


add_executable(${PROJECT_NAME} main.cpp algo/input.cpp algo/algorithms.hpp algo/direction.cpp)

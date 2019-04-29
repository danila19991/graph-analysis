cmake_minimum_required(VERSION 3.8)
project(graph)

enable_testing()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(AlgorithmFiles
        algo/algorithms.hpp
        algo/connectivity.cpp
        algo/graph.cpp
        algo/graph.hpp
        algo/distance.cpp
        algo/similarity.cpp
        algo/centrality.cpp)

set(GrafficFiles graffic/graffic.cpp graffic/graffic.h)

if(UNIX)
    set(FooTestArgs )

    include(GoogleTest)
    add_subdirectory(googletest)
    include_directories(googletest/googletest googletest/googletest/include)

    add_executable(${PROJECT_NAME}_test
            test/test_connectivity.cpp
            test/test_graph.cpp
            test/test_utils.h
            test/test_distance.cpp
            test/test_similarity.cpp
            ${AlgorithmFiles} )

    gtest_add_tests(${PROJECT_NAME}_test "${FooTestArgs}" AUTO)
    target_link_libraries(${PROJECT_NAME}_test gtest gtest_main)
endif()

add_subdirectory(glfw)

set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenGL REQUIRED)

add_executable(${PROJECT_NAME} main.cpp ${AlgorithmFiles} ${GrafficFiles})

target_include_directories(${PROJECT_NAME} PUBLIC ${glfw_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} glfw ${OPENGL_LIBRARIES})

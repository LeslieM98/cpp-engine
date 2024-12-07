cmake_minimum_required(VERSION 3.29)
project(FimbulwinterEngine)

set(CMAKE_CXX_STANDARD 20)

find_package(glm CONFIG REQUIRED)
find_package(spdlog REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

add_subdirectory(dependencies/glad)


add_library(Engine
        include/core/Engine.hpp
        src/core/Engine.cpp
        include/core/System.hpp
        include/component/Position.hpp
        include/component/Health.hpp
        src/component/Health.cpp
        src/component/Position.cpp
        src/core/Component.cpp
        src/core/System.cpp
        include/core/Window.hpp
        src/core/Window.cpp
)
target_link_libraries(Engine PUBLIC glm::glm)
target_link_libraries(Engine PUBLIC spdlog::spdlog_header_only)
target_link_libraries(Engine PUBLIC glad)
target_link_libraries(Engine PUBLIC glfw)
target_include_directories(Engine PUBLIC include)

add_executable(TestMain main.cpp)
target_link_libraries(TestMain PUBLIC Engine)
target_link_libraries(TestMain PUBLIC glad)
target_include_directories(TestMain PUBLIC include)

#include(FetchContent)
#FetchContent_Declare(
#        googletest
#        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
#)
#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
#FetchContent_MakeAvailable(googletest)
#
#enable_testing()
#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
#add_executable(Tests test/test.cpp)
#
#target_link_libraries(Tests PUBLIC
#        GTest::gtest_main
#)
#
#include(GoogleTest)
#gtest_discover_tests(Tests)
cmake_minimum_required(VERSION 3.14)
project(MyProject LANGUAGES CXX)

# Compiler & build settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

# Testing framework setup
include(CTest)
enable_testing()

# GoogleTest setup
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# SFML setup
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.1
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

# Test executable and source files
add_executable(map_parsing_tests
        map_parsing_tests.cpp
        ../src/GameMap.cpp
        ../src/GameMapParse.cpp
)

# Link libraries
target_link_libraries(map_parsing_tests
        gtest_main
        SFML::Graphics
)

# Discover tests
include(GoogleTest)
gtest_discover_tests(map_parsing_tests)

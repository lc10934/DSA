cmake_minimum_required(VERSION 3.20)

project(DSA LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(DEBUG_FLAGS -g -O0)
set(RELEASE_FLAGS -O3 -DNDEBUG)

find_package(GTest REQUIRED)
enable_testing()

file(GLOB MAIN src/main.cpp)
file(GLOB_RECURSE TESTS tst/*.cpp)
file(GLOB_RECURSE HEADERS src/*.hpp)

find_package(fmt REQUIRED)

SET(PACKAGES fmt::fmt)

add_executable(DSA ${MAIN} ${HEADERS})
add_executable(DSA_tests ${TESTS} ${HEADERS})
add_executable(DSA_debug ${MAIN} ${HEADERS})

SET(RELEASE_TARGETS DSA)
SET(TEST_TARGETS DSA_tests)
SET(DEBUG_TARGETS DSA_debug)

foreach (target ${RELEASE_TARGETS})
    target_compile_options(${target} PRIVATE ${RELEASE_FLAGS})
endforeach()

foreach (target ${TEST_TARGETS} ${DEBUG_TARGETS})
    target_compile_options(${target} PRIVATE ${DEBUG_FLAGS})
endforeach()

foreach (target ${RELEASE_TARGETS} ${TEST_TARGETS} ${DEBUG_TARGETS})
    target_include_directories(${target} PUBLIC src)
    target_link_libraries(${target} PRIVATE ${PACKAGES})
endforeach()

# Gtest
find_package(GTest REQUIRED)
target_link_libraries(DSA_tests PRIVATE GTest::gtest_main)

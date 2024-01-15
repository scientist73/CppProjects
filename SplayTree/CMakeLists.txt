########################################################################
#
# CMake build script for Splay Tree.
#
# To run the tests for Splay Tree on Linux, use 'make test' or
# ctest. You can select which tests to run using 'ctest -R regex'.
# For more options, run 'ctest --help'.


option(splay_tree_build_tests "Build all of splay tree's tests." ON)
option(splay_tree_install "Install splay tree lib and tests (if heap_build_tests is ON)." ON)

cmake_minimum_required(VERSION 3.13)
project(splay_tree VERSION 1.0 LANGUAGES CXX)

# Adding google test lib for testing
if(${splay_tree_build_tests})
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/third-party/googletest)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(CMAKE_CXX_COMPILER clang++)



# Where Splay Tree's .h files can be found.
set(splay_tree_build_include_dirs
    "${splay_tree_SOURCE_DIR}/include/splay_tree")

# Splay Tree's .h files
set(splay_tree_headers
    "${splay_tree_SOURCE_DIR}/include/splay_tree/splay_tree.h")
    
########################################################################
#
# Splay Tree's files instalation rule (ON by default)

if (${splay_tree_install})
    set(CPACK_PROJECT_NAME ${PROJECT_NAME})
    set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

    set(CMAKE_INSTALL_PREFIX "${splay_tree_SOURCE_DIR}/install")

    #option(INSTALL_GTEST "Enable installation of googletest. (Projects embedding googletest may want to turn this OFF.)" OFF)

    install(FILES ${splay_tree_headers} DESTINATION "include/splay_tree")

    include(CPack)
endif()



########################################################################
#
# Splay Tree's tests.
#
# The tests are not built by default. To build them, set the
# gtest_build_tests option to ON. You can do it by running ccmake
# or specifying the -Dgtest_build_tests=ON flag when running cmake.


if(${splay_tree_build_tests})
    include(CTest)
    enable_testing()

    add_executable(test_splay_tree "${splay_tree_SOURCE_DIR}/test/test_splay_tree.cpp")
    target_link_libraries(test_splay_tree GTest::gtest_main)
    target_include_directories(test_splay_tree PUBLIC ${splay_tree_build_include_dirs})
    add_test(NAME test_splay_tree COMMAND test_splay_tree)

    include(GoogleTest)
    gtest_discover_tests(test_splay_tree)
endif()
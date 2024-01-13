########################################################################
#
# CMake build script for Heap.
#
# To run the tests for Heap on Linux, use 'make test' or
# ctest. You can select which tests to run using 'ctest -R regex'.
# For more options, run 'ctest --help'.


option(heap_build_tests "Build all of minheap's tests." ON)
option(heap_install "Install heap lib and tests (if heap_build_tests is ON)." ON)


cmake_minimum_required(VERSION 3.13)
project(heap VERSION 1.0 LANGUAGES CXX)

if(${heap_build_tests})
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/third-party/googletest)
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(CMAKE_CXX_COMPILER clang++)



# Where Heap's .h files can be found.
set(heap_build_include_dirs
    "${heap_SOURCE_DIR}/include/heap")

# Heap's .h files
set(heap_headers
    "${heap_SOURCE_DIR}/include/heap/heap.h")
    
########################################################################
#
# Heap's files instalation rule (ON by default)

if (${heap_install})
    set(CPACK_PROJECT_NAME ${PROJECT_NAME})
    set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

    

    #option(INSTALL_GTEST "Enable installation of googletest. (Projects embedding googletest may want to turn this OFF.)" OFF)

    install(FILES ${heap_headers} DESTINATION "include/heap")

    include(CPack)
endif()



########################################################################
#
# Heap's tests.
#
# The tests are not built by default. To build them, set the
# gtest_build_tests option to ON. You can do it by running ccmake
# or specifying the -Dgtest_build_tests=ON flag when running cmake.


if(${heap_build_tests})
    include(CTest)
    enable_testing()

    add_executable(test_heap "${heap_SOURCE_DIR}/test/test_heap.cpp")
    target_link_libraries(test_heap GTest::gtest_main)
    target_include_directories(test_heap PUBLIC ${heap_build_include_dirs})
    #add_test(NAME test_heap COMMAND test_heap)

    include(GoogleTest)
    gtest_discover_tests(test_heap)
endif()
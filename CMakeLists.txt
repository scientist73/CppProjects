cmake_minimum_required(VERSION 3.22)

project(CppProjects)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/third-party/googletest)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Heap)


#add_test(NAME test_heap COMMAND test_heap)


set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/install)
cmake_minimum_required(VERSION 3.22)

project(CppProjects)

#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Heap)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/SplayTree)


#add_test(NAME test_heap COMMAND test_heap)
add_test(NAME test_splay_tree COMMAND test_splay_tree)


set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/install)
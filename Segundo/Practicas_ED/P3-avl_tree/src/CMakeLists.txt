cmake_minimum_required (VERSION 3.1)
project (avl_tree)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb3")

add_executable(test_bstnode test_bstree.cpp avltree.hpp avltree_imp.hpp)
add_executable(test_bstree test_bstree.cpp avltree.hpp avltree_imp.hpp)
add_executable(test_avltnode test_avltree.cpp avltree.hpp avltree_imp.hpp)
add_executable(test_avltree test_avltree.cpp avltree.hpp avltree_imp.hpp)


cmake_minimum_required (VERSION 3.1)
project (graph_traversals)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb3")

set (WGRAPH_DEPENDECIES wgraph.hpp wgraph_imp.hpp
    matrix.hpp matrix.cpp item.hpp)

add_executable(test_wgraph test_wgraph.cpp ${WGRAPH_DEPENDECIES})

add_executable(test_create_graph test_create_graph.cpp city.hpp city.cpp
    ${WGRAPH_DEPENDECIES})

add_executable(test_traversals test_traversals.cpp graph_traversals.hpp
    ${WGRAPH_DEPENDECIES})


add_executable(test_prim test_prim.cpp prim_algorithm.hpp city.hpp city.cpp
    ${WGRAPH_DEPENDECIES})

add_executable(test_kruskal test_kruskal.cpp kruskal_algorithm.hpp
    disjointsets.hpp city.hpp city.cpp ${WGRAPH_DEPENDECIES})

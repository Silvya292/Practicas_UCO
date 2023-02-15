cmake_minimum_required (VERSION 3.1)
project (alphabet_soup)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG  "-O0 -g")
set(CMAKE_CXX_FLAGS "-Wall")
include (CheckIncludeFileCXX)
check_include_file_cxx("cstdint" HAVE_CSTDINT)
if ( HAVE_CSTDINT )
    include(CheckTypeSize)
    check_type_size("uint16_t" SIZEOF_UINT16_T)
endif()

if (NOT SIZEOF_UINT16_T EQUAL 2)
    message(WARNING "Can't find suitable uint16_t")
endif()

add_executable(test_trie_node test_trie_node.cpp trie_node.cpp trie_node.hpp)
add_executable(test_trie test_trie.cpp trie.cpp trie.hpp trie_node.cpp trie_node.hpp)
add_executable(test_alphabet_soup_solver test_alphabet_soup_solver.cpp
    alphabet_soup_solver.cpp alphabet_soup_solver.hpp
    alphabet_soup.cpp alphabet_soup.hpp trie.hpp trie.cpp
    trie_node.cpp trie_node.hpp)

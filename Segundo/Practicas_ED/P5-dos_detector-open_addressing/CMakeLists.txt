cmake_minimum_required (VERSION 3.1)
project (dos_detect-open_adrressing)

# Set a default build type if none was specified
set(default_build_type "Debug")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
      STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

enable_language(CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb3")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -g")

include (CheckIncludeFileCXX)
check_include_file_cxx("cstdint" HAVE_CSTDINT)
if ( HAVE_CSTDINT )
    include(CheckTypeSize)
    check_type_size("uint64_t" SIZEOF_UINT64_T)
endif()

if (NOT SIZEOF_UINT64_T EQUAL 8)
    message(WARNING "Can't find suitable uint64_t")
endif()

add_executable(test_hash_f test_hash_function.cpp hash.hpp hash.cpp)
add_executable(test_ip_utils test_ip_utils.cpp ip_utils.cpp ip_utils.hpp)
add_executable(test_hash_table test_hash_table.cpp hash_table.hpp
    hash_table_imp.hpp ip_utils.hpp ip_utils.cpp hash_table_entry.hpp
    hash_table_entry_imp.hpp hash.cpp hash.hpp)
add_executable(test_dos_detector
    ip_utils.hpp ip_utils.cpp
    hash.hpp hash.cpp
    hash_table.hpp hash_table_imp.hpp
    system.hpp system.cpp
    dos_detector.hpp dos_detector.cpp
    test_dos_detector.cpp)

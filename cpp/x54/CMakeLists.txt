cmake_minimum_required (VERSION 3.16.3)
project (App)

set(CMAKE_PREFIX_PATH "./library/cmake")

find_package(library)
add_executable (App main.cpp)

target_link_libraries (App LINK_PUBLIC Library)
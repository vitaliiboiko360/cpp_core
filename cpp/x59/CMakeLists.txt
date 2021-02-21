cmake_minimum_required(VERSION 3.16)

project(app VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(my_library)

add_executable(app main.cpp)

target_link_libraries(app PUBLIC my_library)

target_include_directories(app PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/my_library"
                          )
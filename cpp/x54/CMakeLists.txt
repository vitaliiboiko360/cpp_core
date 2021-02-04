cmake_minimum_required (VERSION 3.16.3)
project (app)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_PREFIX_PATH "./funx/cmake")

find_package(funx)
add_executable(app main.cpp)

add_subdirectory(funx)
target_link_libraries(app PUBLIC funx)

target_include_directories(app PUBLIC 
"${PROJECT_BINARY_DIR}"
"${PROJECT_SOURCE_DIR}/funx"
)
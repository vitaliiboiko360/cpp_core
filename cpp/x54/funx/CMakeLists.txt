cmake_minimum_required (VERSION 3.16.3)
project (funx VERSION 1.0)

add_library (funx SHARED functions.cpp)

generate_export_header(funx)

configure_file(funx.h.in funx.h)

target_include_directories(funx PUBLIC "${PROJECT_BINARY_DIR}")

install(TARGETS funx DESTINATION lib)
install(FILES funx.h DESTINATION include)
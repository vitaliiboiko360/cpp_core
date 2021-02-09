cmake_minimum_required (VERSION 3.16.3)
project (my_library VERSION 1.0)

add_subdirectory(src)

configure_file(config.h.in config.h)

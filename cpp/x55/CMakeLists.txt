cmake_minimum_required(VERSION 3.16)

# set the project name
project(app VERSION 1.0)

# add the executable
add_executable(app main.cpp)

configure_file(app.h.in app.h)

target_include_directories(app PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )

add_library (my_library SHARED functions.cpp)
target_include_directories(my_library PUBLIC "${PROJECT_BINARY_DIR}")
file(GLOB SOURCES "*.cpp")

add_library(my_library SHARED ${SOURCES})

target_include_directories(my_library PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/..")

install(TARGETS my_library DESTINATION /usr/lib)
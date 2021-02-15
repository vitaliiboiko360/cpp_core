cmake_minimum_required(VERSION 3.16)

project(app)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(OBJS
"/home/user1/uSockets/wolfssl.o"
"/home/user1/uSockets/libuv.o"
"/home/user1/uSockets/socket.o"
"/home/user1/uSockets/gcd.o"
"/home/user1/uSockets/bsd.o"
"/home/user1/uSockets/context.o"
"/home/user1/uSockets/loop.o"
"/home/user1/uSockets/epoll_kqueue.o"
"/home/user1/uSockets/openssl.o"
)

add_executable(app main.cpp ${OBJS})

target_include_directories(app PUBLIC
"/home/user1/uWebSocket/src"
)

target_link_libraries(app PUBLIC
pthread
z
)

set_source_files_properties(
  ${OBJS}
  PROPERTIES
  EXTERNAL_OBJECT true
  GENERATED true
)
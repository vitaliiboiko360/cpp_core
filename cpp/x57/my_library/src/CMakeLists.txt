add_library (my_library SHARED util.cpp client.cpp server.cpp)

target_include_directories(my_library PUBLIC
                            $<BUILD_INTERFACE:${MY_LIBRARY_SOURCE_DIR}/include>
                            $<INSTALL_INTERFACE:include/my_library-${MY_LIBRARY_VERSION}>
                            $<INSTALL_INTERFACE:lib/my_library-${MY_LIBRARY_VERSION}${CMAKE_BUILD_TYPE}>)

install(TARGETS my_library DESTINATION lib/my_library-${MY_LIBRARY_VERSION})
install(FILES client.h config.h DESTINATION include/my_library-${MY_LIBRARY_VERSION})

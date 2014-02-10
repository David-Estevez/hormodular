add_executable( test-sin test_sin.cpp )
set_target_properties(test-sin PROPERTIES COMPILE_FLAGS "${CMAKE_CXX_FLAGS} -lserial")
set_target_properties(test-sin PROPERTIES LINK_FLAGS "-lserial")
target_link_libraries(test-sin serial )

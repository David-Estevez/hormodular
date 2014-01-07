# Testing things #########################################################################################
message( "Building Tests...")

# Testing Module

add_executable( testModule testModule.cpp )
set_target_properties(testModule PROPERTIES COMPILE_FLAGS "${OPENRAVE_CXXFLAGS}")
set_target_properties(testModule PROPERTIES LINK_FLAGS "${OPENRAVE_LINK_FLAGS}")
target_link_libraries(testModule Module ${OpenRAVE_LIBRARIES} ${OpenRAVE_CORE_LIBRARIES} ${Boost_THREAD_LIBRARY} ${CMAKE_THREAD_LIBS_INIT} )


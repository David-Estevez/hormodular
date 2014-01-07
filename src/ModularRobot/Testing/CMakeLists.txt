# Testing things #########################################################################################
message( "Building Tests...")

# Testing ModularRobot

add_executable( testModularRobot testModularRobot.cpp )
set_target_properties(testModularRobot PROPERTIES COMPILE_FLAGS "${OPENRAVE_CXXFLAGS}")
set_target_properties(testModularRobot PROPERTIES LINK_FLAGS "${OPENRAVE_LINK_FLAGS}")
target_link_libraries(testModularRobot ModularRobot Module ${OpenRAVE_LIBRARIES} ${OpenRAVE_CORE_LIBRARIES} ${Boost_THREAD_LIBRARY} ${CMAKE_THREAD_LIBS_INIT} )



# Testing things #########################################################################################
message( "Building ModularRobot Tests...")

# Testing ModularRobot

add_executable( testModularRobot testModularRobot.cpp )
set_target_properties(testModularRobot PROPERTIES COMPILE_FLAGS "${OPENRAVE_CXXFLAGS} ${CMAKE_CXX_FLAGS}")
set_target_properties(testModularRobot PROPERTIES LINK_FLAGS "${OPENRAVE_LINK_FLAGS}")
target_link_libraries(testModularRobot ModularRobot Module ${OpenRAVE_LIBRARIES} ${OpenRAVE_CORE_LIBRARIES} ${Boost_THREAD_LIBRARY} ${CMAKE_THREAD_LIBS_INIT} )


add_executable( testSerialModularRobot testSerialModularRobot.cpp )
set_target_properties(testSerialModularRobot PROPERTIES COMPILE_FLAGS "${OPENRAVE_CXXFLAGS} ${CMAKE_CXX_FLAGS}")
set_target_properties(testSerialModularRobot PROPERTIES LINK_FLAGS "${OPENRAVE_LINK_FLAGS}")
target_link_libraries(testSerialModularRobot ModularRobot Module ${OpenRAVE_LIBRARIES} ${OpenRAVE_CORE_LIBRARIES} ${Boost_THREAD_LIBRARY} ${CMAKE_THREAD_LIBS_INIT} )


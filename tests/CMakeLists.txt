# Testing things #########################################################################################
message( "Building Tests...")

# Testing Gait Table (Broken test)
#add_executable( testGaitTable testGaitTable.cpp )
#target_link_libraries(testGaitTable Controller )

# Testing Sinusoidal Oscillator
add_executable( testSinusoidalOscillator testSinusoidalOscillator.cpp  )
target_link_libraries(testSinusoidalOscillator Controller )

# Testing Module (Broken)
#add_executable( testModule testModule.cpp )
#set_target_properties(testModule PROPERTIES COMPILE_FLAGS "${OPENRAVE_CXXFLAGS} ${CMAKE_CXX_FLAGS}")
#set_target_properties(testModule PROPERTIES LINK_FLAGS "${OPENRAVE_LINK_FLAGS}")
#target_link_libraries(testModule Module ${OpenRAVE_LIBRARIES} ${OpenRAVE_CORE_LIBRARIES} ${Boost_THREAD_LIBRARY} ${CMAKE_THREAD_LIBS_INIT} )

# Testing SimulatedModularRobot 
add_executable( testSimModularRobot testSimModularRobot.cpp )
target_link_libraries(testSimModularRobot ModularRobot )

# Testing SerialModularRobot (broken) [to be fixed?]
#add_executable( testSerialModularRobot testSerialModularRobot.cpp )
#target_link_libraries(testSerialModularRobot ModularRobot )

# Testing SimulatedModularRobotSingleThread 
add_executable( testSimModularRobotSingleThread testSimModularRobotSingleThread.cpp )
target_link_libraries(testSimModularRobotSingleThread ModularRobot )

# Testing Communication with ModularRobot:
add_executable( testSerialCommSinusoidal testSerialCommSinusoidal.cpp )
target_link_libraries(testSerialCommSinusoidal serial )

# Testing Configuration Parser:
add_executable(testConfigParser testConfigParser.cpp)
target_link_libraries(testConfigParser ConfigParser Module)

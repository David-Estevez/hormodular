# Testing things #########################################################################################
add_subdirectory(gtest-1.7.0)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} )


# Test simulated robot interface
add_executable(testSimulatedModularRobotInterface testSimulatedModularRobotInterface.cpp)
target_link_libraries(testSimulatedModularRobotInterface gtest gtest_main)
target_link_libraries(testSimulatedModularRobotInterface ModularRobotInterface)

# Testing Sinusoidal Oscillator
add_executable( testSinusoidalOscillator testSinusoidalOscillator.cpp  )
target_link_libraries(testSinusoidalOscillator gtest gtest_main)
target_link_libraries(testSinusoidalOscillator Oscillator)

# Testing Movement
add_executable( testMovement testMovement.cpp  )
target_link_libraries(testMovement gtest gtest_main)
target_link_libraries(testMovement Oscillator ModularRobotInterface)

# Testing GaitTable
add_executable( testGaitTable testGaitTable.cpp )
target_link_libraries(testGaitTable gtest gtest_main)
target_link_libraries(testGaitTable GaitTable)

# Testing Movement with GaitTable
add_executable( testMovementWithGaitTable testMovementWithGaitTable.cpp  )
target_link_libraries(testMovementWithGaitTable gtest gtest_main)
target_link_libraries(testMovementWithGaitTable Oscillator ModularRobotInterface GaitTable)

# Testing Configuration Parser:
add_executable(testConfigParser testConfigParser.cpp)
target_link_libraries(testConfigParser gtest gtest_main)
target_link_libraries(testConfigParser ConfigParser)

# Testing Connections from ConfigParser
add_executable(testConnectionsFromConfigParser testConnectionsFromConfigParser.cpp)
target_link_libraries(testConnectionsFromConfigParser gtest gtest_main)
target_link_libraries(testConnectionsFromConfigParser Module ConfigParser)

# Testing ModularRobot
add_executable(testModularRobot testModularRobot.cpp)
target_link_libraries(testModularRobot gtest gtest_main)
target_link_libraries(testModularRobot ModularRobot Module ConfigParser Oscillator ModularRobotInterface GaitTable )

# Testing Orientation
add_executable(testOrientation testOrientation.cpp)
target_link_libraries(testOrientation gtest gtest_main)
target_link_libraries(testOrientation Orientation)

# Testing Communication with ModularRobot:
add_executable( testSerialCommSinusoidal testSerialCommSinusoidal.cpp )
target_link_libraries(testSerialCommSinusoidal gtest gtest_main)
target_link_libraries(testSerialCommSinusoidal serial )

# Test robot serial interface
add_executable(testSerialModularRobotInterface testSerialModularRobotInterface.cpp)
target_link_libraries(testSerialModularRobotInterface gtest gtest_main)
target_link_libraries(testSerialModularRobotInterface ModularRobotInterface)

# Testing macro ##########################################################################################
macro( build_controller_test name dependency)
	add_executable( ${name} ${name}.cpp ../${dependency}.cpp)
	set_target_properties(${name} PROPERTIES COMPILE_FLAGS "${OPENRAVE_CXXFLAGS}")
	set_target_properties(${name} PROPERTIES LINK_FLAGS "${OPENRAVE_LINK_FLAGS}")
	target_link_libraries(${name} Controller ${OpenRAVE_LIBRARIES} ${OpenRAVE_CORE_LIBRARIES} ${Boost_THREAD_LIBRARY} )
endmacro( build_controller_test )

macro( configure_controller_test name )
	set_target_properties(${name} PROPERTIES COMPILE_FLAGS "${OPENRAVE_CXXFLAGS}")
	set_target_properties(${name} PROPERTIES LINK_FLAGS "${OPENRAVE_LINK_FLAGS}")
	target_link_libraries(${name} Controller ${OpenRAVE_LIBRARIES} ${OpenRAVE_CORE_LIBRARIES} ${Boost_THREAD_LIBRARY} )
endmacro( configure_controller_test )

# Testing things #########################################################################################
message( "Building Tests...")
# Testing Gait Table
add_executable( testGaitTable testGaitTable.cpp ../GaitTable.cpp)

# Testing Sinusoidal Oscillator
add_executable( testSinusoidalOscillator testSinusoidalOscillator.cpp ../Oscillator.cpp ../SinusoidalOscillator.cpp )

# Testing Controller
find_package( Threads )
add_executable( testController testController.cpp ../../Robot/Robot.cpp ../../SimulationOpenRave/SimulationOpenRave.cpp)
set_target_properties(testController PROPERTIES COMPILE_FLAGS "${OPENRAVE_CXXFLAGS}")
set_target_properties(testController PROPERTIES LINK_FLAGS "${OPENRAVE_LINK_FLAGS}")
target_link_libraries(testController Controller ${OpenRAVE_LIBRARIES} ${OpenRAVE_CORE_LIBRARIES} ${Boost_THREAD_LIBRARY} ${CMAKE_THREAD_LIBS_INIT} )




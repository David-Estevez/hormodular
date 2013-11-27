# Testing macro ##########################################################################################
macro( build_controller_test name dependency)
	add_executable( ${name} ${name}.cpp ../${dependency}.cpp)
	set_target_properties(${name} PROPERTIES COMPILE_FLAGS "${OPENRAVE_CXXFLAGS}")
	set_target_properties(${name} PROPERTIES LINK_FLAGS "${OPENRAVE_LINK_FLAGS}")
	target_link_libraries(${name} Controller ${OpenRAVE_LIBRARIES} ${OpenRAVE_CORE_LIBRARIES} ${Boost_THREAD_LIBRARY} )
endmacro( build_controller_test )

# Testing things #########################################################################################
message( "Building Tests...")
build_controller_test( testGaitTable GaitTable)

# Module #################################################################################################
add_library( Module Module.cpp Servo.cpp SimulatedServo.cpp )
set_target_properties(Module PROPERTIES COMPILE_FLAGS "${OPENRAVE_CXXFLAGS}")
set_target_properties(Module PROPERTIES LINK_FLAGS "${OPENRAVE_LINK_FLAGS}")
target_link_libraries(Module Controller ${OpenRAVE_LIBRARIES} ${OpenRAVE_CORE_LIBRARIES} ${Boost_THREAD_LIBRARY} ${OPENMR} ${CMAKE_THREAD_LIBS_INIT})

# Testing ################################################################################################
add_subdirectory(Testing)

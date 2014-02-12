# Module #################################################################################################
add_library( Module Module.cpp SimulatedModule.cpp SerialModule.cpp Servo.cpp SimulatedServo.cpp SerialServo.cpp)
set_target_properties(Module PROPERTIES COMPILE_FLAGS "${OPENRAVE_CXXFLAGS} ${CMAKE_CXX_FLAGS}")
set_target_properties(Module PROPERTIES LINK_FLAGS "${OPENRAVE_LINK_FLAGS}")
target_link_libraries(Module Controller ${OpenRAVE_LIBRARIES} ${OpenRAVE_CORE_LIBRARIES} ${Boost_THREAD_LIBRARY} ${OPENMR} ${CMAKE_THREAD_LIBS_INIT})

# Testing ################################################################################################
add_subdirectory(Testing)


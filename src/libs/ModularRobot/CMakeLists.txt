# ModularRobot ############################################################################################
add_library( ModularRobot ModularRobot.cpp SimulatedModularRobot.cpp SerialModularRobot.cpp SimulatedModularRobotSingleThread.cpp)
set_target_properties(ModularRobot PROPERTIES COMPILE_FLAGS "${OPENRAVE_CXXFLAGS} ${CMAKE_CXX_FLAGS}")
set_target_properties(ModularRobot PROPERTIES LINK_FLAGS "${OPENRAVE_LINK_FLAGS}")
target_link_libraries(ModularRobot Module SimulationOpenRAVE serial ConfigParser ${OpenRAVE_LIBRARIES} ${OpenRAVE_CORE_LIBRARIES} ${Boost_THREAD_LIBRARY} ${OPENMR} ${CMAKE_THREAD_LIBS_INIT})

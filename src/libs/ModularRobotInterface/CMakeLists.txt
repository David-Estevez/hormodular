# ModularRobotInterface ###################################################################################
add_library( ModularRobotInterface ModularRobotInterfaceFactory.cpp ModularRobotInterface.cpp SimulatedModularRobotInterface.cpp SerialModularRobotInterface.cpp)
target_link_libraries(ModularRobotInterface SimulationOpenRAVE serial ConfigParser ${CMAKE_THREAD_LIBS_INIT})

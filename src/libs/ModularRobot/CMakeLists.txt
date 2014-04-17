# ModularRobot ############################################################################################
add_library( ModularRobot ModularRobot.cpp)
target_link_libraries(ModularRobot Module ConfigParser GaitTable Hormone ModularRobotInterface)


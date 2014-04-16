# Module #################################################################################################
add_library( Module Module.cpp Connector.cpp )
target_link_libraries(Module ConfigParser GaitTable Hormone ModularRobotInterface)


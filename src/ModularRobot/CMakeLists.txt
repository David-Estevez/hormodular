# Module #################################################################################################
add_library( ModularRobot ModularRobot.cpp SimulatedModularRobot.cpp )
set_target_properties(ModularRobot PROPERTIES COMPILE_FLAGS "${OPENRAVE_CXXFLAGS}")
set_target_properties(ModularRobot PROPERTIES LINK_FLAGS "${OPENRAVE_LINK_FLAGS}")
target_link_libraries(ModularRobot ${OpenRAVE_LIBRARIES} ${OpenRAVE_CORE_LIBRARIES} ${Boost_THREAD_LIBRARY} ${OPENMR} ${CMAKE_THREAD_LIBS_INIT})

# Testing ################################################################################################
add_subdirectory(Testing)

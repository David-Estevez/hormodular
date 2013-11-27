# Controller #############################################################################################
add_library( Controller Controller.cpp GaitTable.cpp Oscillator.cpp SinusoidalOscillator.cpp )
set_target_properties(Controller PROPERTIES COMPILE_FLAGS "${OPENRAVE_CXXFLAGS}")
set_target_properties(Controller PROPERTIES LINK_FLAGS "${OPENRAVE_LINK_FLAGS}")
target_link_libraries(Controller ${OpenRAVE_LIBRARIES} ${OpenRAVE_CORE_LIBRARIES} ${Boost_THREAD_LIBRARY})

# Testing ################################################################################################
add_subdirectory(Testing)

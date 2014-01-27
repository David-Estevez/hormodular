# Evolution ###################################################################
add_executable(Evolve
  EvolveController.cpp
  ../Flood/Perceptron/Perceptron.cpp
  ../Flood/MultilayerPerceptron/MultilayerPerceptron.cpp
  ../Flood/ObjectiveFunctional/ObjectiveFunctional.cpp
  ../Flood/TrainingAlgorithm/TrainingAlgorithm.cpp
  ../Flood/TrainingAlgorithm/EvolutionaryAlgorithm.cpp
  Evolution.cpp
  ../Robot/Robot.cpp
  ../SimulationOpenRave/SimulationOpenRave.cpp
  ../Y1ModularRobot/Y1ModularRobot.cpp
  ../Controller/Controller.cpp
  ../FileHandler/FileHandler.cpp
  ../GraphFile/GraphFile.cpp
  ../VisualTracker/VisualTracker.cpp
  ../VisualTracker/disjoint_sets2.cpp
  ../VisualTracker/comp_labeller_interface.cpp
  ../SerialCommunication/SerialCommunication.c
)

### executable
set_target_properties(Evolve PROPERTIES COMPILE_FLAGS "${OPENRAVE_CXXFLAGS}")
set_target_properties(Evolve PROPERTIES LINK_FLAGS "${OPENRAVE_LINK_FLAGS}")
# target_link_libraries(Evolve ${OpenRAVE_LIBRARIES} ${OpenRAVE_CORE_LIBRARIES} ${Boost_THREAD_LIBRARY} ${OpenCV_LIBS} VisualTracker)
target_link_libraries(Evolve ${OpenRAVE_LIBRARIES} ${OpenRAVE_CORE_LIBRARIES} ${Boost_THREAD_LIBRARY} ${OpenCV_LIBS})

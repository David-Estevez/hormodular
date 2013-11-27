### Evaluation #################################################################
add_executable(Evaluate
  EvaluateController.cpp
  ../Flood/Perceptron/Perceptron.cpp
  ../Flood/MultilayerPerceptron/MultilayerPerceptron.cpp
  ../Flood/ObjectiveFunctional/ObjectiveFunctional.cpp  # Only for resolving dependency of TrainingAlgorithm.cpp
  ../Flood/TrainingAlgorithm/TrainingAlgorithm.cpp  # Only for resolving dependency of EvolutionaryAlgorithm.cpp
  ../Flood/TrainingAlgorithm/EvolutionaryAlgorithm.cpp  # Only for resolving dependency of FileHandler.cpp
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

### opencv executable
set_target_properties(Evaluate PROPERTIES COMPILE_FLAGS "${OPENRAVE_CXXFLAGS}")
set_target_properties(Evaluate PROPERTIES LINK_FLAGS "${OPENRAVE_LINK_FLAGS}")
# target_link_libraries(Evaluate ${OpenRAVE_LIBRARIES} ${OpenRAVE_CORE_LIBRARIES} ${Boost_THREAD_LIBRARY} ${OpenCV_LIBS} VisualTracker)
target_link_libraries(Evaluate ${OpenRAVE_LIBRARIES} ${OpenRAVE_CORE_LIBRARIES} ${Boost_THREAD_LIBRARY} ${OpenCV_LIBS})


### Neural Model Evaluator #####################################################
add_executable(NeuralModelEvaluator
  NeuralModelEvaluator.cpp
  ../Flood/Perceptron/Perceptron.cpp
  ../Flood/MultilayerPerceptron/MultilayerPerceptron.cpp
  ../Flood/ObjectiveFunctional/ObjectiveFunctional.cpp  # Only for resolving dependency of TrainingAlgorithm.cpp
  ../Flood/TrainingAlgorithm/TrainingAlgorithm.cpp  # Only for resolving dependency of EvolutionaryAlgorithm.cpp
  ../Flood/TrainingAlgorithm/EvolutionaryAlgorithm.cpp  # Only for resolving dependency of FileHandler.cpp
  ../Robot/Robot.cpp
  ../SimulationOpenRave/SimulationOpenRave.cpp
  ../Controller/Controller.cpp
  ../FileHandler/FileHandler.cpp
  ../GraphFile/GraphFile.cpp
)

set_target_properties(NeuralModelEvaluator PROPERTIES COMPILE_FLAGS "${OPENRAVE_CXXFLAGS}")
set_target_properties(NeuralModelEvaluator PROPERTIES LINK_FLAGS "${OPENRAVE_LINK_FLAGS}")
target_link_libraries(NeuralModelEvaluator ${OpenRAVE_LIBRARIES} ${OpenRAVE_CORE_LIBRARIES} ${Boost_THREAD_LIBRARY})

### Serial Communication Evaluator
add_executable(SerialCommunicationEvaluator
  ../SerialCommunication/SerialCommunicationEvaluator.cpp
  ../SerialCommunication/SerialCommunication.c
)

TARGET_LINK_LIBRARIES(SerialCommunicationEvaluator)


### VisualTracker Evaluator ####################################################
add_executable(VisualTrackerEvaluator
  ../VisualTracker/VisualTrackerApplication.cpp
  ../VisualTracker/VisualTracker.cpp
  ../VisualTracker/disjoint_sets2.cpp
  ../VisualTracker/comp_labeller_interface.cpp
)

# target_link_libraries(VisualTrackerEvaluator ${OpenCV_LIBS} VisualTracker)
target_link_libraries(VisualTrackerEvaluator ${OpenCV_LIBS})


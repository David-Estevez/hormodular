cmake_minimum_required (VERSION 2.6.0)
PROJECT( hormodular )
find_package(OpenRAVE 0.8 REQUIRED)

if( CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX )
  add_definitions("-fno-strict-aliasing -Wall")
endif( CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX )

find_package(Boost ${OpenRAVE_Boost_VERSION} EXACT COMPONENTS iostreams python thread)


set(CMAKE_BUILD_TYPE RelWithDebInfo)

# Make sure the openmr plugin is installed!
# Get the openrave share directory
EXEC_PROGRAM("openrave-config --share-dir" OUTPUT_VARIABLE OpenRAVE_SHARE_DIR)

find_library(OPENMR openmr ${OpenRAVE_SHARE_DIR}/plugins)
message(STATUS "Looking for OpenMR... ${OPENMR}")

if (NOT OPENMR)
  message(SEND_ERROR "OPENMR not found")
endif()


# Include and link directories
include_directories(${OpenRAVE_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR} )
if( Boost_INCLUDE_DIRS )
  include_directories(${Boost_INCLUDE_DIRS})
endif()

link_directories(${OpenRAVE_LIBRARY_DIRS} ${Boost_LIBRARY_DIRS})

FIND_PACKAGE( OpenCV REQUIRED )
MESSAGE("OpenCV_LIBS : ${OpenCV_LIBS}")

### include dirs
INCLUDE_DIRECTORIES(
Evolution Evaluation Robot SimulationOpenRave Y1ModularRobot Controller ServoFeedback
Flood/Utilities Flood/MultilayerPerceptron Flood/ObjectiveFunctional Flood/TrainingAlgorithm
GraphFile FileHandler OscillationAnalyzer_OutputSignal VisualTracker SerialCommunication
)

# add_library(VisualTracker
#   VisualTracker/VisualTracker.cpp
#   VisualTracker/disjoint_sets2.cpp
#   VisualTracker/comp_labeller_interface.cpp
# )

# add_library(camera_utils VisualTracker/camera_utils/camera_utils.cpp)

add_executable(Evolve
  Evolution/EvolveController.cpp
  Flood/Perceptron/Perceptron.cpp
  Flood/MultilayerPerceptron/MultilayerPerceptron.cpp
  Flood/ObjectiveFunctional/ObjectiveFunctional.cpp
  Flood/TrainingAlgorithm/TrainingAlgorithm.cpp
  Flood/TrainingAlgorithm/EvolutionaryAlgorithm.cpp
  Evolution/Evolution.cpp
  Robot/Robot.cpp
  SimulationOpenRave/SimulationOpenRave.cpp
  Y1ModularRobot/Y1ModularRobot.cpp
  Controller/Controller.cpp
 # ServoFeedback/ServoFeedback.cpp
  FileHandler/FileHandler.cpp
  GraphFile/GraphFile.cpp
 # OscillationAnalyzer_OutputSignal/OscillationAnalyzer_OutputSignal.cpp
  VisualTracker/VisualTracker.cpp
  VisualTracker/disjoint_sets2.cpp
  VisualTracker/comp_labeller_interface.cpp
  SerialCommunication/SerialCommunication.c
)

### executable
set_target_properties(Evolve PROPERTIES COMPILE_FLAGS "${OPENRAVE_CXXFLAGS}")
set_target_properties(Evolve PROPERTIES LINK_FLAGS "${OPENRAVE_LINK_FLAGS}")
# target_link_libraries(Evolve ${OpenRAVE_LIBRARIES} ${OpenRAVE_CORE_LIBRARIES} ${Boost_THREAD_LIBRARY} ${OpenCV_LIBS} VisualTracker)
target_link_libraries(Evolve ${OpenRAVE_LIBRARIES} ${OpenRAVE_CORE_LIBRARIES} ${Boost_THREAD_LIBRARY} ${OpenCV_LIBS})


add_executable(Evaluate
  Evaluation/EvaluateController.cpp
  Flood/Perceptron/Perceptron.cpp
  Flood/MultilayerPerceptron/MultilayerPerceptron.cpp
  Flood/ObjectiveFunctional/ObjectiveFunctional.cpp  # Only for resolving dependency of TrainingAlgorithm.cpp
  Flood/TrainingAlgorithm/TrainingAlgorithm.cpp  # Only for resolving dependency of EvolutionaryAlgorithm.cpp
  Flood/TrainingAlgorithm/EvolutionaryAlgorithm.cpp  # Only for resolving dependency of FileHandler.cpp
  Robot/Robot.cpp
  SimulationOpenRave/SimulationOpenRave.cpp
  Y1ModularRobot/Y1ModularRobot.cpp
  Controller/Controller.cpp
 # ServoFeedback/ServoFeedback.cpp
  FileHandler/FileHandler.cpp
  GraphFile/GraphFile.cpp
 # OscillationAnalyzer_OutputSignal/OscillationAnalyzer_OutputSignal.cpp
  VisualTracker/VisualTracker.cpp
  VisualTracker/disjoint_sets2.cpp
  VisualTracker/comp_labeller_interface.cpp
  SerialCommunication/SerialCommunication.c
)

### opencv executable
set_target_properties(Evaluate PROPERTIES COMPILE_FLAGS "${OPENRAVE_CXXFLAGS}")
set_target_properties(Evaluate PROPERTIES LINK_FLAGS "${OPENRAVE_LINK_FLAGS}")
# target_link_libraries(Evaluate ${OpenRAVE_LIBRARIES} ${OpenRAVE_CORE_LIBRARIES} ${Boost_THREAD_LIBRARY} ${OpenCV_LIBS} VisualTracker)
target_link_libraries(Evaluate ${OpenRAVE_LIBRARIES} ${OpenRAVE_CORE_LIBRARIES} ${Boost_THREAD_LIBRARY} ${OpenCV_LIBS})


### Neural Model Evaluator
add_executable(NeuralModelEvaluator
  Evaluation/NeuralModelEvaluator.cpp
  Flood/Perceptron/Perceptron.cpp
  Flood/MultilayerPerceptron/MultilayerPerceptron.cpp
  Flood/ObjectiveFunctional/ObjectiveFunctional.cpp  # Only for resolving dependency of TrainingAlgorithm.cpp
  Flood/TrainingAlgorithm/TrainingAlgorithm.cpp  # Only for resolving dependency of EvolutionaryAlgorithm.cpp
  Flood/TrainingAlgorithm/EvolutionaryAlgorithm.cpp  # Only for resolving dependency of FileHandler.cpp
  Robot/Robot.cpp
  SimulationOpenRave/SimulationOpenRave.cpp
  Controller/Controller.cpp
 # ServoFeedback/ServoFeedback.cpp
  FileHandler/FileHandler.cpp
  GraphFile/GraphFile.cpp
 # OscillationAnalyzer_OutputSignal/OscillationAnalyzer_OutputSignal.cpp
)

set_target_properties(NeuralModelEvaluator PROPERTIES COMPILE_FLAGS "${OPENRAVE_CXXFLAGS}")
set_target_properties(NeuralModelEvaluator PROPERTIES LINK_FLAGS "${OPENRAVE_LINK_FLAGS}")
target_link_libraries(NeuralModelEvaluator ${OpenRAVE_LIBRARIES} ${OpenRAVE_CORE_LIBRARIES} ${Boost_THREAD_LIBRARY})

### Serial Communication Evaluator
add_executable(SerialCommunicationEvaluator
  SerialCommunication/SerialCommunicationEvaluator.cpp
  SerialCommunication/SerialCommunication.c
)

TARGET_LINK_LIBRARIES(SerialCommunicationEvaluator)


### VisualTracker Evaluator
add_executable(VisualTrackerEvaluator
  VisualTracker/VisualTrackerApplication.cpp
  VisualTracker/VisualTracker.cpp
  VisualTracker/disjoint_sets2.cpp
  VisualTracker/comp_labeller_interface.cpp
)

# target_link_libraries(VisualTrackerEvaluator ${OpenCV_LIBS} VisualTracker)
target_link_libraries(VisualTrackerEvaluator ${OpenCV_LIBS})


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

if(NOT OPENMR)
  message(SEND_ERROR "OPENMR not found")
else()
  message(STATUS "OpenMR located at: ${OpenRAVE_SHARE_DIR}/plugins")
endif()


# Include and link directories
include_directories(${OpenRAVE_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR} )
if( Boost_INCLUDE_DIRS )
  include_directories(${Boost_INCLUDE_DIRS})
endif()

link_directories(${OpenRAVE_LIBRARY_DIRS} ${Boost_LIBRARY_DIRS})

FIND_PACKAGE( OpenCV REQUIRED )
MESSAGE("OpenCV_LIBS : ${OpenCV_LIBS}")

### Look for the threads library
find_package(Threads)

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



# Controller #################################################################################
add_subdirectory(Controller)
add_subdirectory(Module)
add_subdirectory(ModularRobot)

# Executables ################################################################################
#add_subdirectory( Evolution )
#add_subdirectory( Evaluation )



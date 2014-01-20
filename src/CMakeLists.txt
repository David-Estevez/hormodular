# Alternative compilations:
#########################################################################################
# For release build, run cmake with this arguments:
#-DCMAKE_BUILD_TYPE=RELEASE
# For debugging purposes compilation, run cmake with this arguments:
#-DCMAKE_BUILD_TYPE=DEBUG
# For debugging and profiling purposes, run cmake with this arguments:
#-DCMAKE_BUILD_TYPE=DEBUG -DCMAKE_CXX_FLAGS=-pg


cmake_minimum_required (VERSION 2.6.0)

# Configure the project:
PROJECT( hormodular )

set(CMAKE_BUILD_TYPE RelWithDebInfo)

if( CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX )
  add_definitions("-fno-strict-aliasing -Wall")
endif( CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX )

# Dependencies
##########################################################################################
# For the simulation:
find_package(OpenRAVE 0.8 REQUIRED)
find_package(Boost ${OpenRAVE_Boost_VERSION} EXACT COMPONENTS iostreams python thread)

# Find openMR
# Get the openrave share directory
EXEC_PROGRAM("openrave-config --share-dir" OUTPUT_VARIABLE OpenRAVE_SHARE_DIR)

find_library(OPENMR openmr ${OpenRAVE_SHARE_DIR}/plugins)
message(STATUS "Looking for OpenMR... ${OPENMR}")

if(NOT OPENMR)
  message(SEND_ERROR "OPENMR not found")
else()
  message(STATUS "OpenMR located at: ${OpenRAVE_SHARE_DIR}/plugins")
endif()


# Thread support:
find_package(Threads)


# For CV robot tracking:
#FIND_PACKAGE( OpenCV REQUIRED )
#MESSAGE("OpenCV_LIBS : ${OpenCV_LIBS}")




# Include and link directories
include_directories(${OpenRAVE_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR} )
if( Boost_INCLUDE_DIRS )
  include_directories(${Boost_INCLUDE_DIRS})
endif()

link_directories(${OpenRAVE_LIBRARY_DIRS} ${Boost_LIBRARY_DIRS})



### include dirs
INCLUDE_DIRECTORIES(
Evolution Evaluation Robot SimulationOpenRave Y1ModularRobot Controller ServoFeedback
Flood/Utilities Flood/MultilayerPerceptron Flood/ObjectiveFunctional Flood/TrainingAlgorithm
GraphFile FileHandler OscillationAnalyzer_OutputSignal VisualTracker SerialCommunication
)

# For the CV robot tracking
# add_library(VisualTracker
#   VisualTracker/VisualTracker.cpp
#   VisualTracker/disjoint_sets2.cpp
#   VisualTracker/comp_labeller_interface.cpp
# )

# add_library(camera_utils VisualTracker/camera_utils/camera_utils.cpp)



# Hormodular internal libs:
##############################################################################################
# Controller #
add_subdirectory(Controller)

# Module #
add_subdirectory(Module)

# ModularRobot #
add_subdirectory(ModularRobot)

# Hormodular main executables ################################################################
#add_subdirectory( Evolution )
#add_subdirectory( Evaluation )



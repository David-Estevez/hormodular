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
find_package(Threads REQUIRED)


# ECF -> Evolutionary Computation Framework
set( ECF_LINK_FLAGS "-lecf" )

# TinyXML2 -> xml parser
FIND_PATH(TINYXML2_INCLUDE_DIR NAMES tinyxml2.h PATHS ${TINYXML2_DIR}${TINYXML2_INCLUDE_DIR} )

IF(TINYXML2_INCLUDE_DIR)
        SET(TINYXML2_FOUND TRUE)
ELSE(TINYXML2_INCLUDE_DIR)
        SET(TINYXML2_FOUND FALSE)
ENDIF(TINYXML2_INCLUDE_DIR)
MARK_AS_ADVANCED(
  TINYXML2_INCLUDE_DIR
)


# Eigen3 -> algebra library
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include_directories(${EIGEN_INCLUDE_DIRS})


# Set output dirs
set (hormodular_TRUNK_DIR "${PROJECT_SOURCE_DIR}")
set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/lib")
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")

# Include and link directories
include_directories(${OpenRAVE_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR} )
include_directories( ${PROJECT_SOURCE_DIR}/src/libs/ConfigParser)
include_directories( ${PROJECT_SOURCE_DIR}/src/libs/SimulationOpenRAVE )
include_directories( ${PROJECT_SOURCE_DIR}/src/libs/Controller)
include_directories( ${PROJECT_SOURCE_DIR}/src/libs/Oscillator)
include_directories( ${PROJECT_SOURCE_DIR}/src/libs/GaitTable)
include_directories( ${PROJECT_SOURCE_DIR}/src/libs/Servo )
include_directories( ${PROJECT_SOURCE_DIR}/src/libs/Module )
include_directories( ${PROJECT_SOURCE_DIR}/src/libs/ModularRobot )
include_directories( ${PROJECT_SOURCE_DIR}/src/libs/ModularRobotInterface )
include_directories( ${PROJECT_SOURCE_DIR}/src/libs/Hormone )
include_directories( ${PROJECT_SOURCE_DIR}/src/libs/Orientation )
include_directories( ${PROJECT_SOURCE_DIR}/src/libs/Utils )

if( Boost_INCLUDE_DIRS )
  include_directories(${Boost_INCLUDE_DIRS})
endif()

link_directories(${OpenRAVE_LIBRARY_DIRS} ${Boost_LIBRARY_DIRS})



# Create output dirs
make_directory(${LIBRARY_OUTPUT_PATH})
make_directory(${EXECUTABLE_OUTPUT_PATH})

# Code is in src folder
add_subdirectory(src)

# Test programs are in tests folder
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin/tests")
add_subdirectory(tests)






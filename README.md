hormodular
==========

Framework for modular robotics locomotion and control research and testing.

This is part of my Bachelor's thesis work.

Author:  [David Estevez Fernandez](https://github.com/David-Estevez)


Index
-------------------------------------------------------------------
 * 1.Introduction
 * 2.Compile and run
  * 2.1.Dependencies
  * 2.2.Compiling
 * 3.Doxygen documentation
 * 4.More info


1. Introduction
---------------------------------------------------------------------
Hormodular is a framework developed to find and test locomotion gaits for modular robots using evolutionary algorithms, as well as to develop and validate different controllers for discovering the robot configuration and selecting the correct gaits.


2. Compile and run
---------------------------------------------------------------------
###2.1. Dependencies###
This software has currently support only for GNU/Linux systems, and it is not guaranteed to work on Windows or Mac platforms. 

The requirements for compiling and using the software are:

#####2.1.1. CMake#####
 [CMake](http://www.cmake.org/) can be installed from the repositories:

    $ sudo apt-get install cmake

#####2.1.2. OpenRAVE#####
Detailed instructions for installing OpenRAVE can be found [here](http://openrave.org/docs/latest_stable/install/). In a Ubuntu-based GNU/Linux system, the commands for installing OpenRAVE from the repositories are:
    
    $ sudo add-apt-repository ppa:openrave/release
    $ sudo apt-get update
    $ sudo apt-get install openrave

Nevertheless, OpenRAVE can also be compiled from sources following the [following instructions](http://openrave.org/docs/latest_stable/coreapihtml/installation.html).

#####2.1.3. OpenMR plugin#####
The original code for OpenMR can be found [here](https://github.com/Obijuan/openmr), although it is no longer maintained by the author, so we recommend downloading the latest version from [our repository](https://github.com/David-Estevez/openmr)

#####2.1.4. ECF #####
Complete instructions for installing ECF can be found [here](http://gp.zemris.fer.hr/ecf/install.html)

 * Download latest ECF (min. 1.3.2) and unzip

 * Install boost:

        sudo apt-get install libboost-dev
    
 * Compile and install ECF:
        
        $ ./configure [ --prefix=DIR ]
        $ make
        $ make install
        
Note: for me, this whole procedure didn't work, but fortunately there is a handy script called 'ecf_install.sh' in the ECF help folder that did work.

 * If you get some error related to the shared library not being found, run this:
        
        export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH

#####2.1.5. TinyXML2 #####
The source for TinyXML2 can be found [here](https://github.com/leethomason/tinyxml2) and can be downloaded using git:

    $ git clone https://github.com/leethomason/tinyxml2

Once it is downloaded, the following commands are used to install it:

    $ mkdir build
    $ cd build
    $ cmake ..
    $ make
    $ sudo make install

#####2.1.5. Eigen3 #####
If Eigen3 is available on the repositories, it can be installed with a single command:

    $ sudo apt-get install libeigen3-dev

Otherwise, the soure code can be downloaded from their [website](), and installed using CMake (no compilation is required, as Eigen is a template library):

    $ mkdir build
    $ cd build
    $ cmake ..
    $ sudo make install


###2.2 Compiling###
#####2.2.1. Using CMake#####
The folder structure used is the typical of a CMake project. In order to compile the project open a terminal in the build directory (hormodular/build) and run this commands:

        $ cmake ..
        $ make

#####2.2.1. Using QtCreator#####
To open the software as a QtCreator project, the only thing needed is to open the main CMakeLists.txt (hormodular/CMakeLists.txt) with QtCreator. This will parse the whole project.
Afterwards, press the "build" icon to build the project.

3. Doxygen documentation
--------------------------------------------------------------------

There is doxygen-generated documentation available for hormodular [here](http://david-estevez.github.io/hormodular).


4. More info
--------------------------------------------------------------------

More info, as well as the whole Bachelor's Thesis, can be found at [(link here)]().

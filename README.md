# CPPND: Capstone Node Editor

This is the repo for the my Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application starting with this repo, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.
# Goal
* Create a prototype of a node base application.
* Resolve the logic associated of traversing the node graph and computing the result.
* Resolve the Propagation of changes (dirty propagation) in the node graph.
* Managing nodes creation, deletion and edition.
* Managing link creation and deletion.


## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* GLFW:
  * linux: sudo apt-get install libglfw3-dev
  * Mac and windows you can see the instructions hire: [GLFW](https://www.glfw.org/)
## Basic Build Instructions

1. Clone this repo:
  * git clone --recursive https://github.com/vfxsnake/Capston_Node_Editor.git
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./capstone_node_editor`.
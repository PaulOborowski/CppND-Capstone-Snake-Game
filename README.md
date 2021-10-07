# CPPND: Capstone Snake Game Example

## Capstone Project:

### New features
* Food is definied within an own class, instead of a SDL_Point. Adapted game and renderer class for use of food object.
* added controls to Food object. use WASD keys.
* added a reverse mode. By pressing space bar, the snake will start hunting for the food automatically. The player plays the role of the food and has to run away from snake using WASD keys.

### New files and classes:
* moved food object functionalities into own class, see food.h
* added snakeplanner class for the reverse mode. It is based on A*-Search from the first lesson.
* adapted controller.h for additional user input keys to place food and activate reverse mode

### Applied C++ features:
* the new features of the game were implemented with focus on applying OOP-techniques and ecapsulating the functionalities of the game. 
* user input for controlling the food position and activation of reverse mode.
* multiple use of for-loops and switch statements in the implementation of the snakeplanner and user input processing. 

### Rubrics points adressed in this project:
* The project demonstrates an understanding of C++ functions and control structures:
  * controller.cpp line 40 to 71: extended case statement for control of food object and activation of autosteer
  * debug.h : added debug functions using preprocessor language
  * snakeplanner.cpp line 82 to 122: using while and if-Statements in the Search-Method
  * snakeplanner.cpp line 131 to 151: using for in ExpandNeighbors-Method
* The project accepts user input and processes the input:
  * controller.cpp line 40 to 71: user input is beaing read to control location of food object and activation of autosteer mode
* The project uses Object Oriented Programming techniques:
  * food.h, food.cpp: added class for graphical food object, which holds the position as private member and updates it at every iteration depending on the state of the game
  * snakeplanner.h, snakeplanner.cpp: added class to enable autosteer functionality of the snake based on AStar Search.
* Classes use appropriate access specifiers for class members:
  * food.h: all members of the class Food are definied as public or private.
  * snakeplanner.h: all members of the class SnakePlanner are definied as public or private.
* Class constructors utilize member initialization lists:
  * snakeplanner.cpp line 8 to 17
  * food.cpp line 6 to 9;
* Classes encapsulate behavior:
  * snakeplanner.h: Methods which are part of AStar-Search are private. User can only access the Update method, which triggers the actual search algoirthm and returns target position of the snake head.
  * food.h: position variables are pviate. User can access position data via GetLoc().
* The project makes use of references in function declarations:
  * food.h line 16: Place method has input reference to Snake object.
  * snakeplanner.h line 21: Update method has input defined as references.

### Build instructions:
* make build - normal build
* make debug - with additional debug message printed in the therminal

### Dependencies
* no change, see below


This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.


## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg

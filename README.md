# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac)
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* [Homebrew](https://brew.sh/)
* SDL2 Image (through homebrew: run `brew install sdl2_image`)
* SDL2 TTF (through homebrew: run `brew install sdl2_ttf`)
* SDL2 Mixer (through homebrew: run `brew install sdl2_mixer`)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`. Note: Due to relative path declarations for image and audio files, the project must be run from the build directory.


## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg

___

#Rubric Items

## Loops, Functions, I/O

*• Criteria: The project demonstrates an understanding of C++ functions and control structures.*

I use if/else conditionals, a while loop, switch statement and for loops throughout the project.

*• Criteria: The project reads data from a file and process the data, or the program writes data to a file.*

I have added the SDL2 Image and SDL2 Mixer libraries to the project in order to use images and audio files in the project. I use an image for a 'new game' button and audio to play a sound when the snake eats food and when the game ends.

*• Criteria: The project accpers user input and processes the input.*

There was an existing switch loop that detected user keyboard input. I added an event to check if a user uses 'left-click' and clicks on the 'new game' which initiates a new game.

## Object Oriented Programming

*• Criteria: The project uses Object Oriented Programming techniques.*

I used the structure that was initially set in the project and added an additional class (Audio) and additional properties to existing classes such as the boolean member 'is_new' on the Snake class.

*• Criteria: Classes use appropriate access specifiers for class members.*

I maintained the structure of the original project and add additional methods and member variables under the appropriate heading (public, private, etc.). For the 'Audio' class, it does not use the same structure but it is open source code that I kept untouched to use in the project (attributed in the header file).

*• Criteria: Class constructors utilize member initialization lists.*

On the renderer class I added for new member variables (results_width, results_height, results_x, results_y) which are initialized on the constructor through the existing member initilization list since it is based on other variables being set.

*• Classes abstract implementation details from their interfaces.*

Any created class or variable used descriptive names (rather than single character variable names) to make the code easily readable.

## Memory Management

*• Criteria: The project makes use of references in function declarations.*

One function that takes this into action that I created is the MousePress method in the Controller class. This takes a reference to the 'snake' and a reference to the button press event and uses the referenced value in the function.

*• Criteria: The project uses destructors appropriately.*

I added to the Renderer destructor method to kill the SDL audio process when the Renderer deallocates. This also deallocates the SDL window. Additionally, when I render the New Game button image, I make sure to destroy and deallocate the surface and texture variables after they are rendered to the screen.

*• Criteria: The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate.*

This was an appropriate feature of drawing the image and additional elements to the screen. For the new image button, the SDL_Rect that is created stays within the scope of the function that it is being used in. Additionally, I chose to load the audio files and keep them in memory the entire time the game runs to speed up the playing of them. If I had to load them freshly every time I wanted to play them, it slowed the game down dramatically.


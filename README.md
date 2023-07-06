# SnakeGame-In-Java
![Language (C++)](https://img.shields.io/badge/powered_by-C++-brightgreen.svg?style=flat-square)


A classic snake game made in C++ using Graphics.h & sfml library.
It will be a good way to learn about different aspect of development with C++ for a beginer.


## Vedio: 
![snacks game](https://github.com/isratjahan829/SnakeGame-In-Java/assets/120164134/acf0c1d9-f7b4-4d9a-a2a7-8e02b80adb40)

## Requirements

#### Must Have (dependencies)
- SFML 2.4.0 or above - http://www.sfml-dev.org/
##### Linux
   
#### MS Build
 * CodeBlocks

## Building from source

### First Method (prefered and used) MS Build

  * Download the source code.
  * Import into CodeBlocks
  * Build according to your need (x64 or x86 or whatever)
   
    ```
    Don't forget to link the sfml libraries - graphics, window and system.
    put the following files in linker input:
     sfml-system-d.lib, sfml-window-d.lib, sfml-graphics-d.lib and GameMenu.lib
    ```
  * Copy the sfml dlls (window, graphics and system) along with the executable
  * Then Run and enjoy
  
 
## Contribution
 
  * Lot's of work remaining.
     * GUI Menu (see https://github.com/ParadoxZero/GameMenu-cpp)
     * Settings and user data save system.
     * Sound
  * In case you are woundering about the extra complication in moving snake -
      That is done in order to smoothen the animation of movement. To have slower/ variable speed of snake
      in *Higher framerate*

Feel free to fork, fix the issues and contribute. Help is always welcome.

This is a simple Snake game implemented in C++ using the graphics library. The game features a snake that moves around the screen and eats fruits to score points. The objective is to control the snake and avoid colliding with its own tail or the game's boundaries.

The game starts with an introduction screen, and then prompts the player to select the difficulty level (easy, medium, or hard). The snake's speed varies based on the chosen difficulty. The game includes features such as score tracking, game over detection, and the option to restart after a game over.

The graphics library is used to render the game elements on the screen, and keyboard inputs are used to control the snake's movement. The game loop continues until the player chooses to exit.


![snacks game](https://github.com/isratjahan829/SnakeGame-In-Java/assets/120164134/acf0c1d9-f7b4-4d9a-a2a7-8e02b80adb40)

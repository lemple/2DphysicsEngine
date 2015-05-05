/*
 Copyright © 2015 Philip Gifford
 SDAGE 1st year 2nd PPP Assignment 2015
*/

// ---------------------------------------------------------------------------------------
/// @file ImageLoader.cpp
/// @brief Calls run from mainGame and runs the game
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------

#include <SDL2/SDL.h>
#include "MainGame.h"

int main()
{
  MainGame mainGame;
  mainGame.run();

  return 0;
}

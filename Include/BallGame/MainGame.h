/*
 Copyright © 2015 Philip Gifford
 SDAGE 1st year 2nd PPP Assignment 2015
*/


// ---------------------------------------------------------------------------------------
/// @file MainGame.h
/// @brief Calls functions from Randini Engine & deals with key input, drawing, deltatime
/// @version 1.0
/// @author Philip Gifford
/// @date 02/05/15
// ---------------------------------------------------------------------------------------

#ifndef __MAINGAME_H_
#define __MAINGAME_H_

#include <Include/Randini/Camera2D.h>
#include <Include/Randini/SpriteLoader.h>
#include <Include/Randini/InputControl.h>
#include <Include/Randini/Window.h>
#include <Include/Randini/GLSLProgram.h>
#include <Include/Randini/Timer.h>
#include <memory>
#include <utility>
#include "BallControl.h"
#include "BallRenderer.h"
#include "BallGrid.h"

#include "boost/random.hpp"
#include "boost/generator_iterator.hpp"

///add boost to add imporved random libary.
///set each different call to certain name
typedef boost::uniform_real<float> RandomDistribution;
typedef boost::uniform_int<int> RandomDistributionInt;
typedef boost::mt19937 RNGType;

///basic enum for gamestate
enum class GameState
{
  PLAY,
  EXIT
};

//Size of the cells
const int CELL_SIZE = 12;

class MainGame
{
public:
  MainGame();

  ~MainGame();

  ///calls init systems,
  ///initBalls
  ///gameLoop
  ///drawGame
  ///update camera from Randini engine
  ///and sets fps limiter for better optimisation
  void run();

private:

  ///sets screen resolution
  ///calls create window from Randini engine
  ///calls spriteLoader from Randini engine to load the ball sprite
  ///sets position of the camera
  ///retrieves the info of the shaders from the file and adds the attributes to the sprites
  ///sets the max FPS so the performance is the same despite using a faster machine
  ///inits render function
  ///inits controller function
  void initSystems();

  ///calls the loop so certain functions and commands will continue to be processed until the game is quit
  ///set the FPS counter using elements fomr the Randini engine
  ///applying deltatime so the game will have a set FPS dependent on the system
  ///calls camera update from Randini Engine
  ///calls drawGame function to continue drawing the game while its running
  void gameLoop();

  ///inits all the different renderers and pushes each one to the stack if they are called
  ///Each function performs a different render
  void initRenderers();

  ///inits all controllers and pushes each one to the stack if they are called
  void initControllers();

  ///Clear buffers & activate textures
  ///draws the balls
  ///grabs the texture uniform from the shader files
  ///unuse texture
  ///swap buffers for the window
  void drawGame();

  ///Inits the 2D grid for spatial partioning
  ///Set number of balls to spawn
  ///Release the balls and assign each one random attributes
  ///Add the ball to the scene and apply the texture to use
  ///Add the ball to the 2D grid
  void initBalls();

  ///Since this updates motion it takes in deltaTime to alter the motions based on the number of ticks
  ///Set the update functrion to the current controller selected and apply the attributes to the ball based on controller selected
  void update(float deltaTime);

  ///Deals with general user input
  ///Deals with gravity controls based on current controller
  ///Deals with user input cycling through renderers
  ///Deals with user input cycling through controllers
  void processInput();


  int m_screenWidth/* = 0*/, m_screenHeight/* = 0*/;
  int m_currentRenderer/* = 0*/;
  int m_currentController/* = 0*/;
  std::vector<Ball> _ball;

  //BallControl m_ballControl;
  //BallRenderer m_ballRenderer;

  std::vector<BallRenderer*> m_ballRenderers;
  std::vector<BallControl*> m_ballControllers;

  //grid of spatial partioning
  std::unique_ptr<BallGrid> m_ballGrid;


  Randini::Window m_window;
  Randini::SpriteLoader m_spriteLoader;
  Randini::Camera2D m_camera;
  Randini::InputControl m_inputControl;
  Randini::GLSLProgram m_textureProgram;
  Randini::FPSLimiter m_fpsLimiter;
	
  float m_fps/* = 0.0f*/;

  GameState _gameState/* = GameState::PLAY*/;


};
#endif


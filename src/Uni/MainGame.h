#pragma once

#include <src/Randini/Camera2D.h>
#include <src/Randini/SpriteLoader.h>
#include <src/Randini/InputControl.h>
#include <src/Randini/Window.h>
#include <src/Randini/GLSLProgram.h>
#include <src/Randini/Timer.h>
#include <memory>
#include <utility>
#include "BallControl.h"
#include "BallRenderer.h"
#include "BallGrid.h"

#include "boost/random.hpp"
#include "boost/generator_iterator.hpp"

typedef boost::uniform_real<float> RandomDistribution;
typedef boost::uniform_int<int> RandomDistributionInt;
typedef boost::mt19937 RNGType;

enum class GameState
{
  PLAY,
  EXIT
};

const int CELL_SIZE = 12;

class MainGame
{
public:
  MainGame() :
    m_screenWidth(0), m_screenHeight(0), m_currentController(0), m_fps(0.0f), _gameState(GameState::PLAY), m_currentRenderer(0)
  {
    m_currentRenderer = 0;
  }

  ~MainGame();
  void run();

private:

  void initSystems();

  void gameLoop();

  void initRenderers();

  void initControllers();

  void update(float deltaTime);

  void drawGame();

  void initBalls();

  void drawHud();

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


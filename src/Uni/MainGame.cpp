
#define _CRT_SECURE_NO_WARNINGS // To shut up the compiler about sprintf...
#include "MainGame.h"
 

#include <src/Randini/ResourceManager.h>
#include <src/Randini/Randini.h>

#include "MainGame.h"

#include <iostream>
#include <SDL2/SDL.h>
#include <random>
#include <ctime>
#include <algorithm>
#include <cmath>

const float DESIRED_FPS = 60.0f;
const int MAX_PHYSICS_STEPS = 6;
const float MS_PER_SECOND = 1000;
const float DESIRED_FRAMETIME = MS_PER_SECOND / DESIRED_FPS;
const float MAX_DELTA_TIME = 1.0f;

MainGame::~MainGame()
{
  for (int i = 0; i < m_ballRenderers.size(); i++)
  {
    delete m_ballRenderers[i];
  }

  for (int i = 0; i < m_ballControllers.size(); i++)
  {
    delete m_ballControllers[i];
  }
}



void MainGame::run()
{
  initSystems();

  initBalls();



  gameLoop();

  m_camera.updateCamera();
  drawGame();
  m_fps = m_fpsLimiter.end();

}

void MainGame::initSystems()
{
  Randini::init();

  m_screenWidth = 1680;
  m_screenHeight = 1050;

  m_window.create("Powered by Randini: Collision", m_screenWidth, m_screenHeight, 0);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  m_camera.init(m_screenWidth, m_screenHeight);
  //point camera to center of the screen
  m_camera.setPosition(glm::vec2(m_screenWidth / 2.0f, m_screenHeight / 2.0f));

  m_spriteLoader.init();

  m_textureProgram.compileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
  m_textureProgram.addAttribute("vertexPosition");
  m_textureProgram.addAttribute("vertexColor");
  m_textureProgram.addAttribute("vertexUV");
  m_textureProgram.linkShader();

  m_fpsLimiter.setMaxFPS(60.0f);

  initRenderers();

  initControllers();
}

void MainGame::gameLoop()
{
  Uint32 previousTicks = SDL_GetTicks();

  while (_gameState == GameState::PLAY) {
    m_fpsLimiter.begin();
    processInput();

    // Calculate the frameTime in milliseconds
    Uint32 newTicks = SDL_GetTicks();
    Uint32 frameTime = newTicks - previousTicks;
    previousTicks = newTicks; // Store newTicks in previousTicks so we can use it next frame
    // Get the total delta time
    float totalDeltaTime = (float)frameTime / DESIRED_FRAMETIME;

    // This counter makes sure the program doesnt spiral to death!
    int i = 0;
    // Loop while we still have steps to process.
    while (totalDeltaTime > 0.0f && i < MAX_PHYSICS_STEPS) {
      // The deltaTime should be the the smaller of the totalDeltaTime and MAX_DELTA_TIME
      float deltaTime = std::min(totalDeltaTime, MAX_DELTA_TIME);
      // Update all physics here and pass in deltaTime

      update(deltaTime);

      // Since we just took a step that is length deltaTime, subtract from totalDeltaTime
      totalDeltaTime -= deltaTime;
      // Increment our frame counter so we can limit steps to MAX_PHYSICS_STEPS
      i++;
    }

    m_camera.updateCamera();
    drawGame();
    m_fps = m_fpsLimiter.end();

		
  }
}

void MainGame::initRenderers()
{
  m_ballRenderers.push_back(new BallRenderer);
  m_ballRenderers.push_back(new PropulsionBallRenderer);
  m_ballRenderers.push_back(new VelocityBallRendererX(m_screenWidth, m_screenHeight));
  m_ballRenderers.push_back(new VelocityBallRendererY(m_screenWidth, m_screenHeight));
}

void MainGame::initControllers()
{
  m_ballControllers.push_back(new BallControl);
  m_ballControllers.push_back(new ColorTransferControl);
}


//defines a spawn for a ball to be added using macros!
struct BallSpawnSystem
{
  BallSpawnSystem(const Randini::ColorRGBA8& color,
  float radius, float mass, float minSpeed,
  float maxSpeed, float prob) :
  color(color),
  radius(radius),
  mass(mass),
  randSpeed(minSpeed, maxSpeed),
  probability(prob)
  {

  }
  Randini::ColorRGBA8 color;
  float radius;
  float mass;
  float probability;
//  std::uniform_real_distribution<float> randSpeed;
  RandomDistribution randSpeed;
};

void MainGame::drawGame()
{
  //set the base dpeth to 1.0
  glClearDepth(1.0);
  //clear the color and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //m_textureProgram.use();

  glActiveTexture(GL_TEXTURE0);

  //grab the camera matrix
  glm::mat4 projectionMatrix = m_camera.getCameraMatrix();
  //GLint pUniform = m_textureProgram.getUniformLocation("P");
  //glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

//	m_spriteLoader.begin();

  //draw balls

  m_currentRenderer = 0;
  m_ballRenderers[m_currentRenderer]->renderBalls(m_spriteLoader, _ball, projectionMatrix);
	

  //m_spriteLoader.end();
//	m_spriteLoader.renderLoader();

  m_textureProgram.use();

  //make shader use texture 0
  GLint textureUniform = m_textureProgram.getUniformLocation("mySampler");
  glUniform1i(textureUniform, 0);

  GLint pUniform = m_textureProgram.getUniformLocation("P");
  glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

  m_textureProgram.unuse();

  m_window.swapBuffers();
}

void MainGame::initBalls()
{
  /*Init grid for spatial partioning!!!!*/

  m_ballGrid = std::unique_ptr<BallGrid>(new BallGrid(m_screenWidth, m_screenHeight, CELL_SIZE));

  //use macro for spawning diffrent balls
  //use ... to let the program know to import all paramters from prentheies
#define ADD_BALL(p, ...) \
  totalProbability += p; \
  possibleBalls.emplace_back(__VA_ARGS__);

  //number of balls to spawn
  const int NUM_BALLS = 15000;

  //random engine
  RNGType randomEngine((unsigned int)time(NULL));
  RandomDistribution randX(0.0f, (float)m_screenWidth);
  RandomDistribution randY(0.0f, (float)m_screenHeight);
  RandomDistribution randDir(-1.0f, 1.0f);

  //RELEASE THE BALLLS HHAHAHAHAHAHAHHA.... thangs
  std::vector <BallSpawnSystem> possibleBalls;
  float totalProbability = 0.0f;
	
  //random vlaues for ball types
  RandomDistribution r1(2.0f, 6.0f);
  RandomDistributionInt r2(0, 255);
  //std::uniform_int_distribution<int> r3(67, 104);
  //std::uniform_int_distribution<int> r4(1, 55);
	
	
  /*
    float radius, float mass, float minSpeed,
    float maxSpeed, float prob) :
  color(color),
    radius(radius),
    mass(mass),
    randSpeed(minSpeed, maxSpeed),
    probability(prob)
  */

  //Adds the balls using macro
  //generate number between 0 and 31 if number is between 0-20 take first ball
  //if 20-30 take second
  //between 30-31 take 3rd ball
  //next is color, next is size of the ball
  // then its mass, the n min speed,
  //then its max speed, finally probability

  //ADD_BALL(1.0f, Randini::ColorRGBA8(235, 62, 62, 255),
  //	2.0f, 2.5f, 0.1f, 3.0f, totalProbability);
//	ADD_BALL(1.0f, Randini::ColorRGBA8(226, 233, 27, 255),
//		2.0f, 2.5f, 0.1f, 3.0f, totalProbability);
  /*ADD_BALL(1.0f, Randini::ColorRGBA8(233, 163, 27, 255),
    3.5f, 4.5f, 0.0f, 0.0f, totalProbability);
  ADD_BALL(1.0f, Randini::ColorRGBA8(233, 163, 27, 255),
    2.5f, 3.5f, 0.0f, 0.0f, totalProbability);
  ADD_BALL(1.0f, Randini::ColorRGBA8(233, 163, 27, 255),
    2.0f, 2.5f, 0.0f, 3.0f, totalProbability);
  ADD_BALL(1.0f, Randini::ColorRGBA8(233, 163, 27, 255),
    1.0f, 1.5f, 0.1f, 3.0f, totalProbability);
  ADD_BALL(1.0f, Randini::ColorRGBA8(233, 163, 27, 255),
    1.5f, 2.0f, 0.1f, 3.0f, totalProbability);
  ADD_BALL(1.0f, Randini::ColorRGBA8(233, 163, 27, 255),
    3.0f, 4.0f, 0.0f, 0.0f, totalProbability);
    */
  for (int i = 0; i < 10000; i++)
  {
    ADD_BALL(1.0f, Randini::ColorRGBA8(r2(randomEngine), r2(randomEngine), r2(randomEngine), 255),
      r1(randomEngine), r1(randomEngine), 0.0f, 0.0f, totalProbability);
  }
	

  //randomd probability
  RandomDistribution spawn(0.0f, totalProbability);

  // Small optimization that sets the size of the internal array to prevent
  // extra allocations
  _ball.reserve(NUM_BALLS);

  //set up to spwan with default valuesss
  BallSpawnSystem* spawningBall = &possibleBalls[0];
  for (int i = 0; i < NUM_BALLS; i++)
  {
    //get ball to spawn roll
    float spawnValue = spawn(randomEngine);
    //find out which ball was picked
    for (size_t j = 0; j < possibleBalls.size(); j++)
    {
      if (spawnValue <= possibleBalls[j].probability)
      {
        spawningBall = &possibleBalls[j];
        break;
      }
    }

    //get random starting position for balls
    glm::vec2 pos(randX(randomEngine), randY(randomEngine));

    //gets random direction
    glm::vec2 direction(randDir(randomEngine), randDir(randomEngine));
    if (direction.x != 0.0f || direction.y != 0.0f)
    {
      direction = glm::normalize(direction);
    }
    else
    {
      //default direction
      direction = glm::vec2(1.0f, 0.0f);
    }

    //add ball
    _ball.emplace_back(spawningBall->radius, spawningBall->mass, pos,
      direction * spawningBall->randSpeed(randomEngine),
      Randini::ResourceManager::getTexture("Textures/zomble/circle.png").id,
      spawningBall->color);


    //add ball to grid
    m_ballGrid->addBall(&_ball.back());


  }
}

void MainGame::update(float deltaTime)
{
  m_ballControllers[m_currentController]->update(_ball, m_ballGrid.get(), deltaTime, m_screenWidth, m_screenHeight);
  //m_ballControl.update(_ball, m_ballGrid.get(),  deltaTime, _screenWidth, _screenHeight);
}

void MainGame::processInput()
{
  //update iunput manager
  m_inputControl.update();


  SDL_Event evnt;
  //Will keep looping until there are no more events to process
  //asks the operating system whats events does it need to process
  //and genrally what the user is clicking
  //begins the loop for the differte key events
  while (SDL_PollEvent(&evnt))
  {
    switch (evnt.type)
    {
      //Calls the EXIT state from the enum
      //overall handles the quit event.
      //this means SDL quit event is reading the quit state
    case SDL_QUIT:
      _gameState = GameState::EXIT;
      break;
    case SDL_MOUSEMOTION:
      //m_ballControl.mouseMotion(_ball, (float)evnt.motion.x, (float)_screenHeight - (float)evnt.motion.y);
      m_ballControllers[m_currentController]->mouseMotion(_ball, (float)evnt.motion.x, (float)m_screenHeight - (float)evnt.motion.y);
      m_inputControl.setMouseCoords((float)evnt.motion.x, (float)evnt.motion.y);
      break;
    case SDL_KEYDOWN:
      m_inputControl.pressKey(evnt.key.keysym.sym);
      break;
    case SDL_KEYUP:
      m_inputControl.releaseKey(evnt.key.keysym.sym);
      break;
    case SDL_MOUSEBUTTONDOWN:
    //	m_ballControl.mouseDown(_ball, (float)evnt.button.x, (float)_screenHeight - (float)evnt.button.y);
      m_ballControllers[m_currentController]->mouseDown(_ball, (float)evnt.button.x, (float)m_screenHeight - (float)evnt.button.y);
      m_inputControl.pressKey(evnt.button.button);
      break;
    case SDL_MOUSEBUTTONUP:
      // m_ballControl.mouseUp(_ball);
      m_ballControllers[m_currentController]->mouseUp(_ball);
      m_inputControl.releaseKey(evnt.button.button);
      break;
    }
  }

  //Handle gravity changes
  //if (m_inputControl.isKeyPressed(SDLK_LEFT)) {
  //	m_ballControl.setGravityDirection(GravityControl::LEFT);
  //}
  //else if (m_inputControl.isKeyPressed(SDLK_RIGHT)) {
  //	m_ballControl.setGravityDirection(GravityControl::RIGHT);
  //}
  //else if (m_inputControl.isKeyPressed(SDLK_UP)) {
  //	m_ballControl.setGravityDirection(GravityControl::UP);
  //}
  //else if (m_inputControl.isKeyPressed(SDLK_DOWN)) {
  //	m_ballControl.setGravityDirection(GravityControl::DOWN);
  //}
  //else if (m_inputControl.isKeyPressed(SDLK_SPACE)) {
  //	m_ballControl.setGravityDirection(GravityControl::NONE);
  //}
  //

  if (m_inputControl.isKeyPressed(SDLK_LEFT)) {
    //m_ballControllers.setGravityDirection(GravityControl::LEFT);
    m_ballControllers[m_currentController]->setGravityDirection(GravityControl::LEFT);
  }
  else if (m_inputControl.isKeyPressed(SDLK_RIGHT)) {
    //m_ballControl.setGravityDirection(GravityControl::RIGHT);
    m_ballControllers[m_currentController]->setGravityDirection(GravityControl::RIGHT);
  }
  else if (m_inputControl.isKeyPressed(SDLK_UP)) {
    //m_ballControl.setGravityDirection(GravityControl::UP);
    m_ballControllers[m_currentController]->setGravityDirection(GravityControl::UP);
  }
  else if (m_inputControl.isKeyPressed(SDLK_DOWN)) {
    //m_ballControl.setGravityDirection(GravityControl::DOWN);
    m_ballControllers[m_currentController]->setGravityDirection(GravityControl::DOWN);
  }
  else if (m_inputControl.isKeyPressed(SDLK_SPACE)) {
    //m_ballControl.setGravityDirection(GravityControl::NONE);
    m_ballControllers[m_currentController]->setGravityDirection(GravityControl::NONE);
  }

  //swap rendered
  if (m_inputControl.isKeyPressed(SDLK_1))
  {
    m_currentRenderer++;
    if (m_currentRenderer >= m_ballRenderers.size())
    {
      m_currentRenderer = 0;
    }
  }

  //swap control
  if (m_inputControl.isKeyPressed(SDLK_2))
  {
    m_currentController++;
    if (m_currentController >= m_ballControllers.size())
    {
      m_currentController = 0;
    }
  }
}



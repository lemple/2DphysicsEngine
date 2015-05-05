/*
 Copyright © 2015 Philip Gifford
 SDAGE 1st year 2nd PPP Assignment 2015
*/

// ---------------------------------------------------------------------------------------
/// @file MainGame.cpp
/// @brief Calls certain files from game engine. Deals with user input and spawsn the balls
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------

#define _CRT_SECURE_NO_WARNINGS // To shut up the compiler about sprintf...
#include "MainGame.h"
 

#include <Include/Randini/ResourceManager.h>
#include <Include/Randini/Randini.h>

#include "MainGame.h"

#include <iostream>
#include <SDL2/SDL.h>
#include <random>
#include <ctime>
#include <algorithm>
#include <cmath>

//-------------------------------------------------------------------------------------------------

const float DESIRED_FPS = 60.0f;
const int MAX_PHYSICS_STEPS = 6;
const float MS_PER_SECOND = 1000;
const float DESIRED_FRAMETIME = MS_PER_SECOND / DESIRED_FPS;
const float MAX_DELTA_TIME = 1.0f;

MainGame::MainGame()  :
  m_screenWidth(0), m_screenHeight(0), m_currentRenderer(0), m_currentController(0), m_fps(0.0f), _gameState(GameState::PLAY)
{
}

//-------------------------------------------------------------------------------------------------

MainGame::~MainGame()
{
  //deletes all newly created renderes
  for (int i = 0; i < (int)m_ballRenderers.size(); i++)
  {
    delete m_ballRenderers[i];
  }

  //deletes all newly created controllers
  for (int i = 0; i < (int)m_ballControllers.size(); i++)
  {
    delete m_ballControllers[i];
  }
}

//-------------------------------------------------------------------------------------------------

void MainGame::run()
{
  initSystems();

  initBalls();

  gameLoop();

  m_camera.updateCamera();
  drawGame();
  m_fps = m_fpsLimiter.end();

}

//-------------------------------------------------------------------------------------------------

void MainGame::initSystems()
{
  Randini::init();
  //set screen resoluton
  m_screenWidth = 1680;
  m_screenHeight = 1050;

  //creates the window by calling m_window from Randini File
  m_window.create("Powered by Randini: Collision", m_screenWidth, m_screenHeight, 0);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  //-------------------------------------------------------------------------------------------------

  m_camera.init(m_screenWidth, m_screenHeight);
  //point camera to center of the screen
  m_camera.setPosition(glm::vec2(m_screenWidth / 2.0f, m_screenHeight / 2.0f));

  //call spriteLoader.init from Randini Engine
  m_spriteLoader.init();

  //calls the vert and frag shader from the file
  //and adds the attributes from the shader file and applys them to the balls
  m_textureProgram.compileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
  m_textureProgram.addAttribute("vertexPosition");
  m_textureProgram.addAttribute("vertexColor");
  m_textureProgram.addAttribute("vertexUV");
  m_textureProgram.linkShader();

  //-------------------------------------------------------------------------------------------------

  //sets MAXFPS from the fps file from Randini Engine
  m_fpsLimiter.setMaxFPS(60.0f);

  //calls init renderers
  initRenderers();

  //calls init controllers
  initControllers();
}

//-------------------------------------------------------------------------------------------------

void MainGame::gameLoop()
{
  //start of each frame calculate how much time has passed
  Uint32 previousTicks = SDL_GetTicks();

  //Standard game loop
  //While the game is running run this loop
  while (_gameState == GameState::PLAY) {

    //call fps limiter from Randini Engine
    m_fpsLimiter.begin();
    processInput();

    // Calculate the frameTime in milliseconds
    Uint32 newTicks = SDL_GetTicks();
    Uint32 frameTime = newTicks - previousTicks;

    // Store newTicks in previousTicks so I can use it next frame
    previousTicks = newTicks;

    //Delta time = desired_FPS / actual fps = 60 / 30 = 2
    float totalDeltaTime = (float)frameTime / DESIRED_FRAMETIME;

    // This counter makes sure the program doesn't spiral to death
    int i = 0;

    // Loop while the program still have steps to process.
    while (totalDeltaTime > 0.0f && i < MAX_PHYSICS_STEPS)
    {
      // The deltaTime should be the the smaller of the totalDeltaTime and MAX_DELTA_TIME
      float deltaTime = std::min(totalDeltaTime, MAX_DELTA_TIME);
      // Update all physics here and pass in deltaTime

      update(deltaTime);

      // Since the program just took a step that is length deltaTime, subtract from totalDeltaTime
      totalDeltaTime -= deltaTime;
      // Increment our frame counter so we can limit steps to MAX_PHYSICS_STEPS
      i++;
     }

    //-------------------------------------------------------------------------------------------------

    //call camera update from Randini game engine and call function updateCamera
    //continue to draw the game while loops is running
    //calls fps end function which will return the FPS
    m_camera.updateCamera();
    drawGame();
    m_fps = m_fpsLimiter.end();
  }
}

//-------------------------------------------------------------------------------------------------

void MainGame::initRenderers()
{
  m_ballRenderers.push_back(new BallRenderer);
  m_ballRenderers.push_back(new PropulsionBallRenderer);
  m_ballRenderers.push_back(new VelocityBallRendererX(m_screenWidth, m_screenHeight));
  m_ballRenderers.push_back(new VelocityBallRendererY(m_screenWidth, m_screenHeight));
}

//-------------------------------------------------------------------------------------------------

void MainGame::initControllers()
{
  m_ballControllers.push_back(new BallControl);
  m_ballControllers.push_back(new ColorTransferControl);
}

//-------------------------------------------------------------------------------------------------

//struct to provide attributes for the balls
//and pass in the values from Ball.h
//defines a spawn for a ball
struct BallSpawnSystem
{
  BallSpawnSystem(const Randini::ColorRGBA8& color,
  float m_radius, float mass, float minSpeed,
  float maxSpeed, float prob) :
  color(color),
  m_radius(m_radius),
  mass(mass),
  probability(prob),
  randSpeed(minSpeed, maxSpeed)
  {

  }
  //calls color settings from Randini Engine
  Randini::ColorRGBA8 color;
  float m_radius;
  float mass;
  float probability;
  //adds random speed to the balls
  RandomDistribution randSpeed;
};

//-------------------------------------------------------------------------------------------------

void MainGame::drawGame()
{
  //set the base depth to 1.0
  glClearDepth(1.0);
  //clear the color and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //activates the texture and sets it to 0
  glActiveTexture(GL_TEXTURE0);

  //grab the camera matrix
  glm::mat4 projectionMatrix = m_camera.getCameraMatrix();

  //links the ball renderer to the current renderer set e.g. currentRender is VelocityBallRendererX
    //and proceeds to render the balls based on the current selected renderer.
    //takes in the spriteLoader form Randini Engine the ball and its attributes, and finally the camera matrix.
  m_ballRenderers[m_currentRenderer]->renderBalls(m_spriteLoader, _ball, projectionMatrix);

  m_textureProgram.use();

  //make shader use texture 0
    //uniform location is "mySample"
  GLint textureUniform = m_textureProgram.getUniformLocation("mySampler");
  glUniform1i(textureUniform, 0);

  GLint pUniform = m_textureProgram.getUniformLocation("P");
  glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

  m_textureProgram.unuse();

  m_window.swapBuffers();
}

//-------------------------------------------------------------------------------------------------

void MainGame::initBalls()
{
  //Init grid for spatial partioning
  //This creates a pointer that that deltes itself when it gets overwritten
  m_ballGrid = std::unique_ptr<BallGrid>(new BallGrid(m_screenWidth, m_screenHeight, CELL_SIZE));

  //number of balls to spawn
  const int NUM_BALLS = 12000;

  //set random engine for each ball spawned allowing for them to appear in different locaiton east time
  RNGType randomEngine((unsigned int)time(0));
  RandomDistribution randX(0.0f, (float)m_screenWidth);
  RandomDistribution randY(0.0f, (float)m_screenHeight);
  RandomDistribution randDir(-1.0f, 1.0f);

  //Release the balls by creating a vector which contains the
    //attributes from the ball spawn struct
  std::vector <BallSpawnSystem> possibleBalls;
  float totalProbability = 0.0f;

  //random values for ball types
    //first randomDistribution for size of the ball
    //second randomDistribution for color of the ball
  RandomDistribution r1(2.0f, 6.0f);
  RandomDistributionInt r2(0, 255);

  //-------------------------------------------------------------------------------------------------

  //run creat ball while i < number of ball
  //Paramters: Color/Size/Mass/Min Speed/Max Speed/probability
  for (int i = 0; i < NUM_BALLS; i++)
  {
    totalProbability += 10;
    possibleBalls.emplace_back(Randini::ColorRGBA8(r2(randomEngine), r2(randomEngine), r2(randomEngine), 255),
      r1(randomEngine), r1(randomEngine), 0.0f, 0.0f, totalProbability);
  }

  //-------------------------------------------------------------------------------------------------

  //random probability
  RandomDistribution spawn(0.0f, totalProbability);

  // Small optimization that sets the size of the internal array to prevent
  // extra allocations
  _ball.reserve(NUM_BALLS);

  //set up to spawn with default values
  //call struct and point it to spawning ball this allows for the spawned ball
  //to hold all the attributes. make reference to prevent copying
  BallSpawnSystem* spawningBall = &possibleBalls[0];

  //-------------------------------------------------------------------------------------------------

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

    //-------------------------------------------------------------------------------------------------

    //get random starting position for balls
    glm::vec2 pos(randX(randomEngine), randY(randomEngine));

    //gets random direction
    glm::vec2 direction(randDir(randomEngine), randDir(randomEngine));

    //if the direction dose not equal 0 then normalize the direction
    if (direction.x != 0.0f || direction.y != 0.0f)
    {
      direction = glm::normalize(direction);
    }
    else
    {
      //default direction
      direction = glm::vec2(1.0f, 0.0f);
    }

    //-------------------------------------------------------------------------------------------------

    //add ball to the m_ball array with each attributes obtained from possibleBall
    //the attributes for possibleBall contains the data from the struct
    //finally obtain the texture to use for the balls from the texture file
    _ball.emplace_back(spawningBall->m_radius, spawningBall->mass, pos,
      direction * spawningBall->randSpeed(randomEngine),
      Randini::ResourceManager::getTexture("Textures/zomble/circle.png").id,
      spawningBall->color);


    //Everytime the program emplace backs a ball add it
    //and pass it into the address of m_ball.back which will get the last element
    //in the vector
    m_ballGrid->addBall(&_ball.back());


  }
}

//-------------------------------------------------------------------------------------------------

void MainGame::update(float _deltaTime)
{
  //calls the controller and set it to the current controller selcted by the user
  //point it to the update function within the BallControl class and pass in each value to the ball
  //This will allow it to update with the current settings based on the controller selected
  m_ballControllers[m_currentController]->update(_ball, m_ballGrid.get(), _deltaTime, m_screenWidth, m_screenHeight);
}

//-------------------------------------------------------------------------------------------------

void MainGame::processInput()
{

  //       MOUSE AND KEYBOARD INPUT PROCESS         //

  //update iunput manager
  m_inputControl.update();

  SDL_Event evnt;

  //Here the program keeps looping until there are no more events to process
  //asks the operating system whats events does it need to process
  //and generally what the user is clicking
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

//-------------------------------------------------------------------------------------------------
  //Set up gravity controls based on the current controller set.
  //Example: If the user inputs the left key the enum value will cycle through to LEFT
  //This will push all the balls in the setr direction
  if (m_inputControl.isKeyPressed(SDLK_LEFT)) {
    m_ballControllers[m_currentController]->setGravityDirection(GravityControl::LEFT);
  }
  else if (m_inputControl.isKeyPressed(SDLK_RIGHT)) {
    m_ballControllers[m_currentController]->setGravityDirection(GravityControl::RIGHT);
  }
  else if (m_inputControl.isKeyPressed(SDLK_UP)) {
    m_ballControllers[m_currentController]->setGravityDirection(GravityControl::UP);
  }
  else if (m_inputControl.isKeyPressed(SDLK_DOWN)) {
    m_ballControllers[m_currentController]->setGravityDirection(GravityControl::DOWN);
  }
  else if (m_inputControl.isKeyPressed(SDLK_SPACE)) {
    m_ballControllers[m_currentController]->setGravityDirection(GravityControl::NONE);
  }

  //-------------------------------------------------------------------------------------------------

  //Swap between render control when the user presses 1
  //When 1 is pressed increment the current render.
  //If the current renderer goes over the amount of renderers available resets back to 0
  if (m_inputControl.isKeyPressed(SDLK_1))
  {
    m_currentRenderer++;
    if (m_currentRenderer >= (int)m_ballRenderers.size())
    {
      m_currentRenderer = 0;
    }
  }

  //-------------------------------------------------------------------------------------------------

  //Swap between ball controllers when the user presses 1
  //When 1 is pressed increment the current controller.
  //If the current controllers goes over the amount of controllers available resets back to 0
  if (m_inputControl.isKeyPressed(SDLK_2))
  {
    m_currentController++;
    if (m_currentController >= (int)m_ballControllers.size())
    {
      m_currentController = 0;
    }
  }
}



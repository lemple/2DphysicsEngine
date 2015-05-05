/*
 Copyright © 2015 Philip Gifford
 SDAGE 1st year 2nd PPP Assignment 2015
*/


// ---------------------------------------------------------------------------------------
/// @file BallRenderer.h
/// @brief Contolrs different renders and inits the shaders and textures
/// @version 1.0
/// @author Philip Gifford
/// @date 02/05/15
// ---------------------------------------------------------------------------------------

#ifndef __BALLRENDERER_H_
#define __BALLRENDERER_H_

//-------------------------------------------------------------------------------------------------

#include <Include/Randini/SpriteLoader.h>
#include <Include/Randini/GLSLProgram.h>

#include <memory>
#include <vector>
#include "Ball.h"

//-------------------------------------------------------------------------------------------------


//renders the balls
class BallRenderer
{
public:
  BallRenderer() : m_program(NULL)
  {
    ;
  }
  /**
   * @brief initShaders
   * As soon as the program calls render balls with a program which is null it will allocate a new one
   * Inits all shaders from GLSL shader located in Randini Engine
   * Adds the attributes and links the shaders
   */
  void initShaders();

  //-------------------------------------------------------------------------------------------------

  /**
   * @brief renderBalls
   * Make this a virtual function as I want to derive form this
   * Imports the sprites from the game engine
   * renders a list of balls to render all the balls
   * Instead of rendering a single ball loop through all the balls
   * @param _spriteLoader
   *                Imports the spriteLoader from Randini enabling the sprties to be loaded
   * @param _balls
   *                Takes the data of balls to allow them to be rendered
   * @param _projectionMatrix
   *                Grabs camera matrix as its needed for the uniform sampler
   *
   */
  virtual void renderBalls(Randini::SpriteLoader& _spriteLoader, const std::vector <Ball>& _balls,
                                                              const glm::mat4& _projectionMatrix);

  //-------------------------------------------------------------------------------------------------

protected:
  std::unique_ptr<Randini::GLSLProgram> m_program;
};

//-------------------------------------------------------------------------------------------------

/**
 * @brief PropulsionBallRenderer
 * The PropulsionBallRenderer class
 * When balls increase in velocity they become brighter
 * Set new renderer using same elements from renderBalls but altered
 * inherits the virtual function
 */
class PropulsionBallRenderer : public BallRenderer
{
public:
  ///

  /**
   * @brief renderBalls
   * Since it inherits from renderballs add it to public.
   * Unfortunately override was a c++11 so there's no way to ensure of this
   * @param _spriteLoader
   *                Imports the spriteLoader so it canrender balls with new renderer
   * @param _balls
   *                Takes the data of balls to allow them to be rendered
   * @param _projectionMatrix
   *                Grabs camera matrix as its needed for the uniform sampler
   */
  virtual void renderBalls(Randini::SpriteLoader& _spriteLoader, const std::vector <Ball>& _balls,
                                                              const glm::mat4& _projectionMatrix);

  //-------------------------------------------------------------------------------------------------

};

/**
 * @brief The VelocityBallRendererX class
 * Visualise the velocity of ball renderers when moving in the x direction
 * as well as visualise the position with different colours
 */
class VelocityBallRendererX : public BallRenderer
{
public:

  /**
   * @brief VelocityBallRendererX
   * Visualise the velocity of ball renderers when moving in the x direction
   *
   * @param screenWidth
   *                Takes the screenWidth of the window
   * @param screenHeight
   *                Takes the screenHeight of the window
   */
  VelocityBallRendererX(int screenWidth, int screenHeight);

  //-------------------------------------------------------------------------------------------------

  /**
   * @brief renderBalls
   * Since it inherits from renderballs add it to public.
   *  Unfortunately override was a c++11 so there's no way to ensure of this
   *
   * @param _spriteLoader
   *              Imports the spriteLoader so it canrender balls with new renderer
   * @param _balls
   *              Takes the data of balls to allow them to be rendered
   * @param _projectionMatrix
   *              Grabs camera matrix as its needed for the uniform sampler
   */
  virtual void renderBalls(Randini::SpriteLoader& _spriteLoader, const std::vector <Ball>& _balls,
                                                              const glm::mat4& _projectionMatrix);

  //-------------------------------------------------------------------------------------------------

private:
  //Get the location of the screen
  int m_screenWidth;
  int m_screenHeight;
};

/**
 * @brief The VelocityBallRendererY class
 * Visualise the velocity of ball renderers when moving in the y direction
 * as well as visualise the position with different colours
 */
class VelocityBallRendererY : public BallRenderer
{
public:
  /**
   * @brief VelocityBallRendererY
   * Visualise the velocity of ball renderers when moving in the y direction
   *
   * @param _screenWidth
   *                    Takes the screenWidth of the window
   * @param _screenHeight
   *                    Takes the screenHeight of the window
   */
  VelocityBallRendererY(int _screenWidth, int _screenHeight);

  //-------------------------------------------------------------------------------------------------

  /**
   * @brief renderBalls
   * Since it inherits from renderballs add it to public.
   *  Unfortunately override was a c++11 so there's no way to ensure of this
   *
   * @param _spriteLoader
   *              Imports the spriteLoader so it canrender balls with new renderer
   * @param _balls
   *              Takes the data of balls to allow them to be rendered
   * @param _projectionMatrix
   *              Grabs camera matrix as its needed for the uniform sampler
   */
  virtual void renderBalls(Randini::SpriteLoader& _spriteLoader, const std::vector <Ball>& _balls,
                                                              const glm::mat4& _projectionMatrix);

  //-------------------------------------------------------------------------------------------------

private:
  int m_screenWidth;
  int m_screenHeight;
};
#endif


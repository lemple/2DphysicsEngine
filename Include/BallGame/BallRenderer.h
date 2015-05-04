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

#include <Include/Randini/SpriteLoader.h>
#include <Include/Randini/GLSLProgram.h>

#include <memory>
#include <vector>
#include "Ball.h"


//renders the balls
class BallRenderer
{
public:
  BallRenderer() : m_program(NULL)
  {
    ;
  }

  ///As soon as the program calls render balls with a program whihc is null it will allocate a new one
  ///Inits all shaders from GLSL shader located in Randini Engine
  ///Adds the attributes and links the shaders
  void initShaders();


  ///Make this a virtual function as I want to derive form this
  ///Imports the sprites from the game engine
  ///renders a list of balls to render all the balls
  ///Instead of rendering a single ball loop through all the balls
  virtual void renderBalls(Randini::SpriteLoader& spriteLoader, const std::vector <Ball>& balls, const glm::mat4& projectionMatrix);

protected:
  std::unique_ptr<Randini::GLSLProgram> m_program;
 // Randini::GLSLProgram* m_program /*= nullptr*/; //stuff...

};

///When balls increase in velocity they become brighter
///Set new renderer using same elements from renderBalls but altered
///inherits the virtual function
class PropulsionBallRenderer : public BallRenderer
{
public:
  ///Since it inherits from renderballs add it to public. Unfortunately override was a c++11 so there's no way to ensure of this
  virtual void renderBalls(Randini::SpriteLoader& spriteLoader, const std::vector <Ball>& balls, const glm::mat4& projectionMatrix) /*override*/; //...thaaaangs

};

///Visualise the velocity of ball renderers when moving in the x direction
///as well as visualise the position with different colours
class VelocityBallRendererX : public BallRenderer
{
public:
  //Since it registers velocity il inherit the function as well as render balls
  VelocityBallRendererX(int screenWidth, int screenHeight);
  virtual void renderBalls(Randini::SpriteLoader& spriteLoader, const std::vector <Ball>& balls, const glm::mat4& projectionMatrix) /*override*/;

private:
  //Get the location of the screen
  int m_screenWidth;
  int m_screenHeight;
};

///Visualise the velocity of ball renderers when moving in the y direction
///as well as visualise the position with different colours
class VelocityBallRendererY : public BallRenderer
{
public:
  VelocityBallRendererY(int screenWidth, int screenHeight);
  virtual void renderBalls(Randini::SpriteLoader& spriteLoader, const std::vector <Ball>& balls, const glm::mat4& projectionMatrix) /*override*/;

private:
  int m_screenWidth;
  int m_screenHeight;
};
#endif


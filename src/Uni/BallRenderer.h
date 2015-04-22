#pragma once

#include <src/Randini/SpriteLoader.h>
#include <src/Randini/GLSLProgram.h>

#include <memory>
#include <vector>
#include "Ball.h"


//renders the balls
class BallRenderer
{

public:

  void initShaders();

  virtual void renderBalls(Randini::SpriteLoader& spriteLoader, const std::vector <Ball>& balls, const glm::mat4& projectionMatrix);

protected:
  std::unique_ptr<Randini::GLSLProgram> m_program;
};

class PropulsionBallRenderer : public BallRenderer
{
public:
  virtual void renderBalls(Randini::SpriteLoader& spriteLoader, const std::vector <Ball>& balls, const glm::mat4& projectionMatrix) override;

};

class VelocityBallRendererX : public BallRenderer
{
public:
  VelocityBallRendererX(int screenWidth, int screenHeight);
  virtual void renderBalls(Randini::SpriteLoader& spriteLoader, const std::vector <Ball>& balls, const glm::mat4& projectionMatrix) override;

private:
  int m_screenWidth;
  int m_screenHeight;
};

class VelocityBallRendererY : public BallRenderer
{
public:
  VelocityBallRendererY(int screenWidth, int screenHeight);
  virtual void renderBalls(Randini::SpriteLoader& spriteLoader, const std::vector <Ball>& balls, const glm::mat4& projectionMatrix) override;

private:
  int m_screenWidth;
  int m_screenHeight;
};


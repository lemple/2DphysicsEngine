/*
 Copyright © 2015 Philip Gifford
 SDAGE 1st year 2nd PPP Assignment 2015
*/

#include "BallRenderer.h"

// ---------------------------------------------------------------------------------------
/// @file BallRenderer.cpp
/// @brief Outputs different rederers, applys shaders to the balls and renders all the balls
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------

void BallRenderer::initShaders()
{
  //only inits the program if its needed
  if (m_program == NULL)
  {
    m_program = std::unique_ptr<Randini::GLSLProgram>(new Randini::GLSLProgram());
    m_program->compileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
    m_program ->addAttribute("vertexPosition");
    m_program->addAttribute("vertexColor");
    m_program->addAttribute("vertexUV");
    m_program->linkShader();
  }
}

//-------------------------------------------------------------------------------------------------

void BallRenderer::renderBalls(Randini::SpriteLoader& _spriteLoader, const std::vector<Ball>& _balls, const glm::mat4& _projectionMatrix)
{
  glClearColor(0.16f, 0.14f, 0.14f, 1.0f);

  initShaders();

  ////////////////////////////////////////////////////
  //In between m_program.use and m_program.unuse
  //going to link all shader uniforms
  m_program->use();

  //in-between program begin the sprite loder
  _spriteLoader.begin();

  //make shader use texture 0
  //Take same code from mainGame.draw function
  glActiveTexture(GL_TEXTURE0);
  GLint textureUniform = m_program->getUniformLocation("mySampler");
  glUniform1i(textureUniform, 0);

  //grab the camera matrix but don't need to upload
  GLint pUniform = m_program->getUniformLocation("P");
  glUniformMatrix4fv(pUniform, 1, GL_FALSE, &_projectionMatrix[0][0]);

  //render all the balls
  for(std::vector<Ball>::const_iterator ball = _balls.begin();
      ball != _balls.end();
      ball++)
  {

    glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
    const glm::vec4 destRect(ball->m_position.x - ball->m_radius, ball->m_position.y - ball->m_radius, ball->m_radius * 2.0f, ball->m_radius * 2.0f);

  //prepares the glyphs to be drawn
    _spriteLoader.draw(destRect, uvRect, ball->m_textureId, 0.0f, ball->m_color);
  }

  _spriteLoader.end();
  _spriteLoader.renderLoader();

  m_program->unuse();
}

//-------------------------------------------------------------------------------------------------

void PropulsionBallRenderer::renderBalls(Randini::SpriteLoader& _spriteLoader, const std::vector <Ball>& _balls, const glm::mat4& _projectionMatrix)
{
///FOLLOWS SAME BASIC PRINCIPLE FROM RENDERBALLS

  initShaders();

  m_program->use();

  _spriteLoader.begin();

  //make shader use texture 0
  GLint textureUniform = m_program->getUniformLocation("mySampler");
  glUniform1i(textureUniform, 0);

  //grab the camera matrix
  GLint pUniform = m_program->getUniformLocation("P");
  glUniformMatrix4fv(pUniform, 1, GL_FALSE, &_projectionMatrix[0][0]);

  //-------------------------------------------------------------------------------------------------

  //render all the balls
  for(std::vector<Ball>::const_iterator ball = _balls.begin();
      ball != _balls.end();
      ball++)
  {
    glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
    const glm::vec4 destRect(ball->m_position.x - ball->m_radius, ball->m_position.y - ball->m_radius, ball->m_radius * 2.0f, ball->m_radius * 2.0f);

  //Here I start changing the renderer to determine brightness of the balls based on velocity

  //Takes color RGBA values from Randini game engine
  //takes the length of the velocity/magnitude of velocity and multiply it by the balls mass
  //this will then be the balls momentum and clamps the values between 0-255 using glm::clamp
  //multiply by 12 to increase the effect
    Randini::ColorRGBA8 color;
    GLubyte colorValue = (GLubyte)(glm::clamp(glm::length(ball->m_velocity) * ball->m_mass * 12, 0.0f, 255.0f));
    color.r = colorValue;
    color.g = colorValue;
    color.b = colorValue;
    color.a = colorValue;

    _spriteLoader.draw(destRect, uvRect, ball->m_textureId, 0.0f, color);
  }

  //-------------------------------------------------------------------------------------------------

  _spriteLoader.end();
  _spriteLoader.renderLoader();

  m_program->unuse();
}


//-------------------------------------------------------------------------------------------------

VelocityBallRendererX::VelocityBallRendererX(int _screenWidth, int _screenHeight) :
m_screenWidth(_screenWidth),
m_screenHeight(_screenHeight)
{

}

//-------------------------------------------------------------------------------------------------

void VelocityBallRendererX::renderBalls(Randini::SpriteLoader& _spriteLoader, const std::vector <Ball>& _balls, const glm::mat4& _projectionMatrix)
{
  ///FOLLOWS SAME BASIC PRINCIPLE FROM RENDERBALLS

  initShaders();

  m_program->use();

  _spriteLoader.begin();

  //make shader use texture 0
  GLint textureUniform = m_program->getUniformLocation("mySampler");
  glUniform1i(textureUniform, 0);

  //grab the camera matrix
  GLint pUniform = m_program->getUniformLocation("P");
  glUniformMatrix4fv(pUniform, 1, GL_FALSE, &_projectionMatrix[0][0]);

  //-------------------------------------------------------------------------------------------------

  //render all the balls
  //  for (auto& ball : balls)
  for(std::vector<Ball>::const_iterator ball = _balls.begin();
      ball != _balls.end();
      ball++)
  {

    //-------------------------------------------------------------------------------------------------

    glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
    const glm::vec4 destRect(ball->m_position.x - ball->m_radius, ball->m_position.y - ball->m_radius, ball->m_radius * 2.0f, ball->m_radius * 2.0f);

    Randini::ColorRGBA8 color;

    //-------------------------------------------------------------------------------------------------

  //make float multiplier to multiply easier
  //Multiplyu it by the velocity and clamp again
  //use the position to apply different colors to different location of the screen
  //By applying a special case which allows to specify the window location
  //take location of balls position and divide by screenWidth
  //creating a number between 0-1 and multiply by 255
    float multi = 100.0f;
    GLubyte colorValue = (GLubyte)(glm::clamp(ball->m_velocity.x * multi, 0.0f, 255.0f));
    color.r = 150;
    color.g = (GLubyte)(ball->m_position.x / m_screenWidth * 255.0f);
    color.b = (GLubyte)(ball->m_position.y / m_screenHeight * 255.0f);
    color.a = colorValue;

    _spriteLoader.draw(destRect, uvRect, ball->m_textureId, 0.0f, color);
  }

  //-------------------------------------------------------------------------------------------------

  _spriteLoader.end();
  _spriteLoader.renderLoader();

  m_program->unuse();
}

//-------------------------------------------------------------------------------------------------

VelocityBallRendererY::VelocityBallRendererY(int _screenWidth, int _screenHeight) :
m_screenWidth(_screenWidth),
m_screenHeight(_screenHeight)
{

}

//-------------------------------------------------------------------------------------------------

//Same scenario as VelocityBallRendererX but change values to Y direction
void VelocityBallRendererY::renderBalls(Randini::SpriteLoader& _spriteLoader, const std::vector <Ball>& _balls, const glm::mat4& _projectionMatrix)
{

  initShaders();

  m_program->use();

  _spriteLoader.begin();

  //make shader use texture 0
  GLint textureUniform = m_program->getUniformLocation("mySampler");
  glUniform1i(textureUniform, 0);

  //grab the camera matrix
  GLint pUniform = m_program->getUniformLocation("P");
  glUniformMatrix4fv(pUniform, 1, GL_FALSE, &_projectionMatrix[0][0]);

  //-------------------------------------------------------------------------------------------------

  //render all the balls
  for(std::vector<Ball>::const_iterator ball = _balls.begin();
      ball != _balls.end();
      ball++)
  {

    //-------------------------------------------------------------------------------------------------

    glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
    const glm::vec4 destRect(ball->m_position.x - ball->m_radius, ball->m_position.y - ball->m_radius, ball->m_radius * 2.0f, ball->m_radius * 2.0f);

    Randini::ColorRGBA8 color;

    float multi = 100.0f;
    GLubyte colorValue = (GLubyte)(glm::clamp(ball->m_velocity.y * multi, 0.0f, 255.0f));
    color.r = 128;
    color.g = (GLubyte)(ball->m_position.x / m_screenWidth * 255.0f);
    color.b = (GLubyte)(ball->m_position.y / m_screenHeight * 255.0f);
    color.a = colorValue;

    _spriteLoader.draw(destRect, uvRect, ball->m_textureId, 0.0f, color);
  }

  //-------------------------------------------------------------------------------------------------

  _spriteLoader.end();
  _spriteLoader.renderLoader();

  m_program->unuse();
}




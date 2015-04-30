
#include "BallRenderer.h"



//void BallRenderer::renderBall(Randini::SpriteLoader& spriteLoader, Ball& ball)
//{
//  glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
//  const glm::vec4 destRect(ball.position.x - ball.radius, ball.position.y - ball.radius, ball.radius * 2.0f, ball.radius * 2.0f);

//  spriteLoader.draw(destRect, uvRect, ball.textureId, 0.0f, ball.color);
//}

void BallRenderer::initShaders()
{
  if (m_program == NULL)
  {
    //m_program = std::make_unique<Randini::GLSLProgram>();
    //m_program = new Randini::GLSLProgram();
    m_program = std::unique_ptr<Randini::GLSLProgram>(new Randini::GLSLProgram());
    m_program->compileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
    m_program ->addAttribute("vertexPosition");
    m_program->addAttribute("vertexColor");
    m_program->addAttribute("vertexUV");
    m_program->linkShader();
  }
}

void BallRenderer::renderBalls(Randini::SpriteLoader& spriteLoader, const std::vector<Ball>& balls, const glm::mat4& projectionMatrix)
{
  glClearColor(0.16f, 0.14f, 0.14f, 1.0f);
	
  initShaders();

  m_program->use();

  spriteLoader.begin();

  //make shader use texture 0
  glActiveTexture(GL_TEXTURE0);
  GLint textureUniform = m_program->getUniformLocation("mySampler");
  glUniform1i(textureUniform, 0);

  //grab the camera matrix
	
  GLint pUniform = m_program->getUniformLocation("P");
  glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

  //render all the balls
  //for (auto& ball : balls)
  for(std::vector<Ball>::const_iterator ball = balls.begin();
      ball != balls.end();
      ball++)
  {
    glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
    const glm::vec4 destRect(ball->position.x - ball->radius, ball->position.y - ball->radius, ball->radius * 2.0f, ball->radius * 2.0f);

    spriteLoader.draw(destRect, uvRect, ball->textureId, 0.0f, ball->color);
  }

  spriteLoader.end();
  spriteLoader.renderLoader();

  m_program->unuse();
}


void PropulsionBallRenderer::renderBalls(Randini::SpriteLoader& spriteLoader, const std::vector <Ball>& balls, const glm::mat4& projectionMatrix)
{
	

  initShaders();

  m_program->use();

  spriteLoader.begin();

  //make shader use texture 0
  GLint textureUniform = m_program->getUniformLocation("mySampler");
  glUniform1i(textureUniform, 0);

  //grab the camera matrix

  GLint pUniform = m_program->getUniformLocation("P");
  glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

  //render all the balls
//  for (auto& ball : balls)
  for(std::vector<Ball>::const_iterator ball = balls.begin();
      ball != balls.end();
      ball++)
  {
    glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
    const glm::vec4 destRect(ball->position.x - ball->radius, ball->position.y - ball->radius, ball->radius * 2.0f, ball->radius * 2.0f);

    Randini::ColorRGBA8 color;
    GLubyte colorValue = (GLubyte)(glm::clamp(glm::length(ball->velocity) * ball->mass * 12, 0.0f, 255.0f));
    color.r = colorValue;
    color.g = colorValue;
    color.b = colorValue;
    color.a = colorValue;

    spriteLoader.draw(destRect, uvRect, ball->textureId, 0.0f, color);
  }

  spriteLoader.end();
  spriteLoader.renderLoader();

  m_program->unuse();
}


VelocityBallRendererX::VelocityBallRendererX(int screenWidth, int screenHeight) :
m_screenWidth(screenWidth),
m_screenHeight(screenHeight)
{

}

void VelocityBallRendererX::renderBalls(Randini::SpriteLoader& spriteLoader, const std::vector <Ball>& balls, const glm::mat4& projectionMatrix)
{
	

  initShaders();

  m_program->use();

  spriteLoader.begin();

  //make shader use texture 0
  GLint textureUniform = m_program->getUniformLocation("mySampler");
  glUniform1i(textureUniform, 0);

  //grab the camera matrix

  GLint pUniform = m_program->getUniformLocation("P");
  glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

  //render all the balls
//  for (auto& ball : balls)
  for(std::vector<Ball>::const_iterator ball = balls.begin();
      ball != balls.end();
      ball++)
  {
    glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
    const glm::vec4 destRect(ball->position.x - ball->radius, ball->position.y - ball->radius, ball->radius * 2.0f, ball->radius * 2.0f);

    Randini::ColorRGBA8 color;

    float multi = 100.0f;
    GLubyte colorValue = (GLubyte)(glm::clamp(ball->velocity.x * multi, 0.0f, 255.0f));
    color.r = 150;
    color.g = (GLubyte)(ball->position.x / m_screenWidth * 255.0f);
    color.b = (GLubyte)(ball->position.y / m_screenHeight * 255.0f);
    color.a = colorValue;

    spriteLoader.draw(destRect, uvRect, ball->textureId, 0.0f, color);
  }

  spriteLoader.end();
  spriteLoader.renderLoader();

  m_program->unuse();
}


VelocityBallRendererY::VelocityBallRendererY(int screenWidth, int screenHeight) :
m_screenWidth(screenWidth),
m_screenHeight(screenHeight)
{

}

void VelocityBallRendererY::renderBalls(Randini::SpriteLoader& spriteLoader, const std::vector <Ball>& balls, const glm::mat4& projectionMatrix)
{

  initShaders();

  m_program->use();

  spriteLoader.begin();

  //make shader use texture 0
  GLint textureUniform = m_program->getUniformLocation("mySampler");
  glUniform1i(textureUniform, 0);

  //grab the camera matrix

  GLint pUniform = m_program->getUniformLocation("P");
  glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

  //render all the balls
//  for (auto& ball : balls)
//  {
  for(std::vector<Ball>::const_iterator ball = balls.begin();
      ball != balls.end();
      ball++)
  {
    glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
    const glm::vec4 destRect(ball->position.x - ball->radius, ball->position.y - ball->radius, ball->radius * 2.0f, ball->radius * 2.0f);

    Randini::ColorRGBA8 color;

    float multi = 100.0f;
    GLubyte colorValue = (GLubyte)(glm::clamp(ball->velocity.y * multi, 0.0f, 255.0f));
    color.r = 128;
    color.g = (GLubyte)(ball->position.x / m_screenWidth * 255.0f);
    color.b = (GLubyte)(ball->position.y / m_screenHeight * 255.0f);
    color.a = colorValue;

    spriteLoader.draw(destRect, uvRect, ball->textureId, 0.0f, color);
  }

  spriteLoader.end();
  spriteLoader.renderLoader();

  m_program->unuse();
}




#pragma once
#include <vector>

//By storing all the ball components into Ball.h it has to be called
//In each section so I can take the components and use them.fb
#include "Ball.h"

enum class GravityControl { NONE, LEFT, UP, RIGHT, DOWN };


///I found that any method to improve compile time would be beneficial and therefore
///used a forward deceleration to allow my program to compile faster.
///Forward deceleration for the ballGrid
class BallGrid;


//implements the logic for the balls and allows them to be controlled
class BallControl
{
public:
  BallControl()
    : m_grabbedBall(-1), m_prevPosition(glm::vec2(0.0f)), m_cursorOffset(glm::vec2(0.0f)), m_gravityControl(GravityControl::NONE)
  {;}

  //////////////////////////////UPDATE BALLS////////////////////////////////////////////////

  ///Function intakes the vector of the balls which derives from Ball class so therefore
  ///all values can be set.
  ///BallGrid to allow the input of the 2D grid to update each ball with spatial partitioning
  ///Delta time as all function need to be set to deltaTime, set mxX and maxY for wall collision detection.
  virtual void update(std::vector <Ball>& balls, BallGrid* ballGrid, float deltaTime, int maxX, int maxY);

  void setGravityDirection(GravityControl dir) { m_gravityControl = dir; }

  ///  MouseBallChecker: Takes X and Y location for the mouse so it can be located to the location of the ball			         ///
  ///  MouseDown: Takes in the values of the balls so they can be altered depending if the ball is grabbed                   ///
  ///  Also location of the mouse for when the mouse is clicked down 										                                     ///
  ///  MouseUP: Takes the values of the balls and apply's them new values when mouse is released               	             ///
  ///  MouseMotion: Takes the general location of the cursor and allows the ball to follow the mouse cursor                  ///
  ///  UpdateCollision: Takes in the BallGrid class so the balls can be checked for collision with other balls on the grid   ///
  ///  CollisisonChecker: Detects the collision made between a ball and a vector of balls starting at a specific index       ///
  virtual bool mouseBallChecker(Ball& b, float mouseX, float mouseY);
  virtual void mouseDown(std::vector <Ball>& balls, float mouseX, float mouseY);
  virtual void mouseUp(std::vector <Ball>& balls);
  virtual void mouseMotion(std::vector <Ball>& balls, float mouseX, float mouseY);
  virtual void updateCollision(BallGrid* ballGrid);
  virtual void collisionChecker(Ball* ball, std::vector<Ball*>& ballsToCheck, int startingIndex);

  //checks collision between two balls
  virtual void collisionChecker(Ball& b1, Ball& b2);

  ///vec 2 varible for direction of the gravity movement
  glm::vec2 getGravityMovement();

  //give the grabbed ball an index of -1 to be registerd in the vector of balls
  int m_grabbedBall/* = -1*/;

  //glm to deal with mathematics of collision
  //prevPosition is to work out the speed of the ball based on its previous position
  glm::vec2 m_prevPosition/* = glm::vec2(0.0f)*/;
  glm::vec2 m_cursorOffset/* = glm::vec2(0.0f)*/;

  GravityControl m_gravityControl/* = GravityControl::NONE*/;

};

class ColorTransferControl : public BallControl
{
public:
  glm::vec2 getGravityMovement();

  virtual bool mouseBallChecker(Ball& b, float mouseX, float mouseY);
  virtual void mouseDown(std::vector <Ball>& balls, float mouseX, float mouseY);
  virtual void mouseUp(std::vector <Ball>& balls);
  virtual void mouseMotion(std::vector <Ball>& balls, float mouseX, float mouseY);

  virtual void update(std::vector <Ball>& balls, BallGrid* ballGrid, float deltaTime, int maxX, int maxY);
  virtual void updateCollision(BallGrid* ballGrid) /*override*/;
  virtual void collisionChecker(Ball* ball, std::vector<Ball*>& ballsToCheck, int startingIndex) /*override*/;
  virtual void collisionChecker(Ball& b1, Ball& b2) /*override*/;


};

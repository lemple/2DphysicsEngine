/*
 Copyright © 2015 Philip Gifford
 SDAGE 1st year 2nd PPP Assignment 2015
*/


// ---------------------------------------------------------------------------------------
/// @file BallControl.h
/// @brief Handle different ball controls and tracks mouse for grabbing
/// @version 1.0
/// @author Philip Gifford
/// @date 02/05/15
// ---------------------------------------------------------------------------------------

#ifndef __BALLCONTROL_H_
#define __BALLCONTROL_H_

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


  /**
   * @brief update
   * Function intakes the vector of the balls which derives from Ball class so therefore
   * all values can be set.
   * set mxX and maxY for wall collision detection.
   *
   * @param _balls
   * @param _ballGrid
   *              BallGrid to allow the input of the 2D grid to update
   *              each ball with spatial partitioning
   * @param _deltaTime
   *              DeltaTime is set to keep motion at a fix rate
   * @param _maxX
   *              Set for wall collision in X direction
   * @param _maxY
   *              Set for wall collision in Y direction
   */
  virtual void update(std::vector <Ball>& _balls, BallGrid* _ballGrid, float _deltaTime, int _maxX, int _maxY);


  /**
   * @brief setGravityDirection
   * Sets gravity direction control and allows the user
   * to manipulate the direction of the balls
   * @param
   *      dir sets direction of the ball
   */
  void setGravityDirection(GravityControl dir) { m_gravityControl = dir; }



  /**
   * @brief mouseDown Takes in the values of the balls so they can be
   * altered depending if the ball is grabbed
   * @param _balls
   * @param _mouseX
   * @param _mouseY
   */
  virtual void mouseDown(std::vector <Ball>& _balls, float _mouseX, float _mouseY);

  /**
   * @brief mouseUp takes the values of the balls and apply's them new values when mouse is released
   *
   * @param _balls
   */
  virtual void mouseUp(std::vector <Ball>& _balls);

  /**
   * @brief
   * mouseMotion takes the general location of the cursor
   * and allows the ball to follow the mouse cursor
   * @param _balls
   *              Sets the ball and allows it to be affected by the mosue
   * @param _mouseX
   *              Gets the coordinates of the mouse in x axis
   * @param _mouseY
   *              Gets the coordinates of the mouse in y axis
   */
  virtual void mouseMotion(std::vector <Ball>& _balls, float _mouseX, float _mouseY);

  /**
   * @brief mouseBallChecker
   * Takes X and Y location for the
   * mouse so it can be located to the location of the ball
   * Also location of the mouse for when the mouse is clicked down
   *
   * @param _b
   *          Set for returning the ball values
   * @param _mouseX
   *          Set gets the coordinates of the mouse in X axis
   * @param _mouseY
   *          Set gets the coordinates of the mouse in X axis
   * @return
   *          The coordinates of the mous linked to ball position
   */
  virtual bool mouseBallChecker(Ball& _b, float _mouseX, float _mouseY);

  /**
   * @brief updateCollision
   * Takes in the BallGrid class so the balls can be
   * checked for collision with other balls on the grid
   * @param _ballGrid
   *                Checks the ballGrid
   */
  virtual void updateCollision(BallGrid* _ballGrid);

  /**
   * @brief collisionChecker Detects the collision made between a ball
   * and a vector of balls starting at a specific index
   * @param _ball
   * @param _ballsToCheck
   * @param _startingIndex
   */
  virtual void collisionChecker(Ball* _ball, std::vector<Ball*>& _ballsToCheck, int _startingIndex);

  //checks collision between two balls
  /**
   * @brief collisionChecker Detects the collision between two balls in same cell
   * @param _b1
   * @param _b2
   */
  virtual void collisionChecker(Ball& _b1, Ball& _b2);

  ///vec 2 varible for direction of the gravity movement
  glm::vec2 getGravityMovement();

  //give the grabbed ball an index of -1 to be registerd in the vector of balls
  int m_grabbedBall;

  //glm to deal with mathematics of collision
  //prevPosition is to work out the speed of the ball based on its previous position
  glm::vec2 m_prevPosition;
  glm::vec2 m_cursorOffset;

  GravityControl m_gravityControl;

};

///////All code the same compared to BallControl class aside from being able to transfer colour!///////
class ColorTransferControl : public BallControl
{
public:
  glm::vec2 getGravityMovement();

  virtual bool mouseBallChecker(Ball& _b, float _mouseX, float _mouseY);

  virtual void mouseDown(std::vector <Ball>& _balls, float _mouseX, float _mouseY);

  virtual void mouseUp(std::vector <Ball>& _balls);

  virtual void mouseMotion(std::vector <Ball>& _balls, float _mouseX, float _mouseY);

  virtual void update(std::vector <Ball>& _balls, BallGrid* _ballGrid, float _deltaTime, int _maxX, int _maxY);

  virtual void updateCollision(BallGrid* _ballGrid);

  virtual void collisionChecker(Ball* _ball, std::vector<Ball*>& _ballsToCheck, int _startingIndex);

  virtual void collisionChecker(Ball& _b1, Ball& _b2);


};
#endif

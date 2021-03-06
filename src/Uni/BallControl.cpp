/*
 Copyright © 2015 Philip Gifford
 SDAGE 1st year 2nd PPP Assignment 2015
*/

#include "BallControl.h"
#include "BallGrid.h"

// ---------------------------------------------------------------------------------------
/// @file BallControl.cpp
/// @brief Sets up multiple controls for the ball and deals with wall collision
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------

void BallControl::update(std::vector <Ball>& _balls, BallGrid* _ballGrid, float _deltaTime, int _maxX, int _maxY)
{
  const float FRICTION = 0.04f;

  //update balls that have been grabbed with new velocity
  //if the ball is not equal to -1 it means that we have successfully grabbed the ball
  //this will then apply the new velocity of the ball allowing it to move
  if (m_grabbedBall != -1)
  {
    //sets the throwing algorithm in place
    //this means the velocity of the ball will equal to the distance between the throw
    //if the ball new position is small the velocity will be slow if its big the velocity will be large
    //CODE TAKEN FROM: http://answers.unity3d.com/questions/38429/how-can-i-calculate-velocity-without-using-rigidbo.html
    _balls[m_grabbedBall].m_velocity = _balls[m_grabbedBall].m_position - m_prevPosition;

  }

  //assign vec2 to the getter for gravity movement
  glm::vec2 gravity = getGravityMovement();

  //-------------------------------------------------------------------------------------------------

  for (size_t i = 0; i < _balls.size(); i++)
  {
   //sets a handle for better efficiently
   Ball& ball = _balls[i];
   //update the momentum and gravity of the ball if its not grabbed
   if ((int)i != m_grabbedBall)
   {
     //if ball is not grabbed set ball position + velocity
     //this allows for the ball to move across the screen
     ball.m_position += ball.m_velocity * _deltaTime;

     //applies friction to the balls dependent on there m_mass
     glm::vec2 movementVec = ball.m_velocity * ball.m_mass;

     //if the movement vector does not equal 0 for both x and y
     //then apply friction to the balls
     if (movementVec.x != 0 || movementVec.y != 0)
     {
       //If friction is less then the movement of the balls
       if (FRICTION < glm::length(movementVec))
       {
         //Here I multiply the velocity by the value of the friction. Then multiply movement and return the 2 vectors with a length of one
         //Therefore the balls are in motion and apply the maths to add velocity dependent on the friction settings
         //and finally set the velocity based on the m_mass by dividing.
         ball.m_velocity -= _deltaTime * FRICTION * glm::normalize(movementVec) / ball.m_mass;
       }
       else
       {
         //set the movement to 0 as the balls have stopped moving
         ball.m_velocity = glm::vec2(0.0f);
       }
     }
     //apply gravity to the balls
     ball.m_velocity += gravity * _deltaTime;
   }

   //-------------------------------------------------------------------------------------------------

   //check wall collision
   //here if the ball position is less then its m_radius
   //I set the position to be equal to the balls m_radius
   if (ball.m_position.x < ball.m_radius)
   {
     ball.m_position.x = ball.m_radius;
     if (ball.m_velocity.x < 0) ball.m_velocity.x *= -1;
   }
   //If the ball raidus is greater then the maxX it means there had been a collision
   //with the wall. This will then push the ball off the wall based on the balls velocity
   else if (ball.m_position.x + ball.m_radius >= _maxX)
   {
     //detects when the ball edge has hit the wall and push it away
     //and if the ball is moving and hits the wall reduce its velocity
     //by a small amount
     ball.m_position.x = _maxX - ball.m_radius - 1;
     if (ball.m_velocity.x > 0) ball.m_velocity.x *= -1;
   }
   if (ball.m_position.y < ball.m_radius)
   {
     ball.m_position.y = ball.m_radius;
     if (ball.m_velocity.y < 0) ball.m_velocity.y *= -1;
   }
   else if (ball.m_position.y + ball.m_radius >= _maxY)
   {
     ball.m_position.y = _maxY - ball.m_radius - 1;
     if (ball.m_velocity.y > 0) ball.m_velocity.y *= -1;
   }

   //-------------------------------------------------------------------------------------------------

   //Checks to see if the ball position has changed:
   //store cell in a new cell and check it with the cells position
   Cell* newCell = _ballGrid->getCell(ball.m_position);

   //Check to see if the new cell is not part of the leader/owner cell
   //However in order to perform this task I originally needed to loop through the whole
   //vector which could cause a worst case scenario on having to search through the whole vector.
   //To fix this I kept track of the cells location in the vector to look up the position immediately
   //by setting cell index equal to the balls position in the cell. (this scenario can be found in ball.h and ballGrid.cpp)
   if (newCell != ball.m_cellLeader)
   {
     //If this is the case then the ball will be moved
     //Remove it from its cell
     _ballGrid->removeBall(&_balls[i]);

     //Handles moving the balls between all different cells
     _ballGrid->addBall(&_balls[i], newCell);
   }
 }

  //-------------------------------------------------------------------------------------------------

 //update all collisions
 updateCollision(_ballGrid);

 if (m_grabbedBall != -1)
 {
   _balls[m_grabbedBall].m_velocity = _balls[m_grabbedBall].m_position - m_prevPosition;
   m_prevPosition = _balls[m_grabbedBall].m_position;
 }
}

//-------------------------------------------------------------------------------------------------

//sets the gravity controls for 4 directions
glm::vec2 BallControl::getGravityMovement()
{
 const float GRAVITY_FORCE = 0.1f;
 glm::vec2 gravity;

 switch (m_gravityControl)
 {
 //if the value of gravity is set to DOWN by the user
 //set x as 0 and apply the gravity force to the -y direction to make gravity go down
 //alter each vec2 based on direction
 case GravityControl::DOWN:
   gravity = glm::vec2(0.0f, -GRAVITY_FORCE);
   break;
 case GravityControl::UP:
   gravity = glm::vec2(0.0f, GRAVITY_FORCE);
   break;
 case GravityControl::LEFT:
   gravity = glm::vec2(-GRAVITY_FORCE, 0.0f);
   break;
 case GravityControl::RIGHT:
   gravity = glm::vec2(GRAVITY_FORCE, 0.0f);
   break;
 case GravityControl::NONE:
   break;
 }
 return gravity;
}

//-------------------------------------------------------------------------------------------------

//deals with when the ball is grabbed
//refer to ballControl.h for more info about parameters
void BallControl::mouseDown(std::vector <Ball>& _balls, float _mouseX, float _mouseY)
{
 //If the ball is located in the same location of the mouse as its clicked then apply
 //grabbed ball values
 for (size_t i = 0; i < _balls.size(); i++)
 {
   if (mouseBallChecker(_balls[i], _mouseX, _mouseY))
   {
     m_grabbedBall = i;
     m_cursorOffset = glm::vec2(_mouseX, _mouseY) - _balls[i].m_position;
     m_prevPosition = _balls[i].m_position;
     _balls[i].m_velocity = glm::vec2(0.0f);
   }
 }
}

//-------------------------------------------------------------------------------------------------

//refer to BallControl.h for more info on function
void BallControl::mouseUp(std::vector <Ball>& _balls)
{
 //if the mouse is released
 if (m_grabbedBall != -1)
 {
   //apply the same maths as found above
 //CODE TAKEN FROM: http://answers.unity3d.com/questions/38429/how-can-i-calculate-velocity-without-using-rigidbo.html
   _balls[m_grabbedBall].m_velocity = _balls[m_grabbedBall].m_position - m_prevPosition;
 //set ball to released
   m_grabbedBall = -1;
 }
}

//-------------------------------------------------------------------------------------------------

//refer to BallControl.h for more info on function
void BallControl::mouseMotion(std::vector <Ball>& _balls, float _mouseX, float _mouseY)
{
 //if ball is grabbed
 if (m_grabbedBall != -1)
 {
 //balls position will be relative to the position of the cursor - the offset for precise grabbing
   _balls[m_grabbedBall].m_position = glm::vec2(_mouseX, _mouseY) - m_cursorOffset;
 }
}

//-------------------------------------------------------------------------------------------------

bool BallControl::mouseBallChecker(Ball& b, float _mouseX, float _mouseY)
{
 return (_mouseX >= b.m_position.x - b.m_radius && _mouseX < b.m_position.x + b.m_radius &&
     _mouseY >= b.m_position.y - b.m_radius && _mouseY < b.m_position.y + b.m_radius);
}

//-------------------------------------------------------------------------------------------------

//Update the collision of the cells so use an L shape for best spatial partinong
void BallControl::updateCollision(BallGrid* _ballGrid)
{
 //iterate through all the grid spots
 //and finds out how many rows we have
 for (int i = 0; i < (int)_ballGrid->m_cells.size(); i++)
 {
   //how far into a given row is the program
  //use modulo to gain the remainder
   int x = i % _ballGrid->m_numCellsX;
   //how many rows do we have
   int y = i / _ballGrid->m_numCellsX;

   //Store the handle to the grid to cell
   Cell& cell = _ballGrid->m_cells[i];

   //-------------------------------------------------------------------------------------------------

   //Need to check through collision with our ball and a vector of balls
   //loop through all balls in a cell
   for (int j = 0; j < (int)cell.balls.size(); j++)
   {
     //make ball handle to make code look nicer
     Ball* ball = cell.balls[j];

     //Check with own cell using collisionChecker function
     //use cell.balls for the vector of balls to check and for starting index put j + 1
     //So program updates after itself
     collisionChecker(ball, cell.balls, j + 1);

     //-------------------------------------------------------------------------------------------------

     //update collision with neighbour cells
     //Uses the L format http://gameprogrammingpatterns.com/spatial-partition.html
     //Check collision with ball then get the cell in the grid.
     //In parameters is the cell the program will check. Since the ball is not checking with itself set to 0
     if (x > 0)
     {
       //check in left direction
       collisionChecker(ball, _ballGrid->getCell(x - 1, y)->balls, 0);
       if (y > 0)
       {
         //check in top left direction
         collisionChecker(ball, _ballGrid->getCell(x - 1, y - 1)->balls, 0);
       }
       if (y < _ballGrid->m_numCellsY - 1)
       {
         //check in bottom left direction
         collisionChecker(ball, _ballGrid->getCell(x - 1, y + 1)->balls, 0);
       }
     }

     //-------------------------------------------------------------------------------------------------
     //check in up cell direction
     if (y > 0)
     {
       collisionChecker(ball, _ballGrid->getCell(x, y - 1)->balls, 0);
     }
   }
  }
}

//-------------------------------------------------------------------------------------------------

//The reason for this function is to check collision easily and check collision with our own cell without
//duplicating any code
//StartingIndex is used when checking in the same cell with another ball to prevent multiple checking
void BallControl::collisionChecker(Ball* ball, std::vector<Ball*>& ballsToCheck, int startingIndex)
{
 //iterates through balls in starting index
 for (int i = startingIndex; i < (int)ballsToCheck.size(); i++)
 {
   //Use *ball to prevent having to change a bunch of code and will get
   //the value of ball and will be able to be passed in as reference
   collisionChecker(*ball, *ballsToCheck[i]);
 }
}

//-------------------------------------------------------------------------------------------------


//check for collision
//CODE RECIVED FOMR HERE http://stackoverflow.com/posts/345863/edit
//Here I used an elastic collision between balls

///@brief Elastic collision
///Modified from :- if collision depth
///Jay Conrad 2008
///Avalible from: http://stackoverflow.com/posts/345863/edit
void BallControl::collisionChecker(Ball& b1, Ball& b2)
{
 //Here I define the vecotr collision
 glm::vec2 distVec = b2.m_position - b1.m_position;
 glm::vec2 distDir = glm::normalize(distVec);

 //Here I intake the length of distVec to find out the distance
 float distance = glm::length(distVec);
 //The m_radius equals both ball one and ball 2 m_radius combined
 float m_radius = b1.m_radius + b2.m_radius;

 float collisionDepth = m_radius - distance;

 //if there was a collision the apply the maths
 if (collisionDepth > 0)
 {
   //Here I need to worry about the elastic collision between the two balls the velocity and the direction when they will
   //when they collide
   b1.m_position -= distDir * collisionDepth * (b2.m_mass / b1.m_mass) * 0.5f;
   b2.m_position += distDir * collisionDepth * (b1.m_mass / b2.m_mass) * 0.5f;


   float aci = glm::dot(b1.m_velocity, distDir);
   float bci = glm::dot(b2.m_velocity, distDir);

   float acf = (aci * (b1.m_mass - b2.m_mass) + 2 * b2.m_mass * bci) / (b1.m_mass + b2.m_mass);
   float bcf = (bci * (b2.m_mass - b1.m_mass) + 2 * b1.m_mass * aci) / (b1.m_mass + b2.m_mass);

   b1.m_velocity += (acf - aci) * distDir;
   b2.m_velocity += (bcf - bci) * distDir;
 }
}
/// End of citation

//-------------------------------------------------------------------------------------------------


glm::vec2 ColorTransferControl::getGravityMovement()
{
 const float GRAVITY_FORCE = 0.1f;
 glm::vec2 gravity;

 switch (m_gravityControl)
 {
 case GravityControl::DOWN:
   gravity = glm::vec2(0.0f, -GRAVITY_FORCE);
   break;
 case GravityControl::UP:
   gravity = glm::vec2(0.0f, GRAVITY_FORCE);
   break;
 case GravityControl::LEFT:
   gravity = glm::vec2(-GRAVITY_FORCE, 0.0f);
   break;
 case GravityControl::RIGHT:
   gravity = glm::vec2(GRAVITY_FORCE, 0.0f);
   break;
 case GravityControl::NONE:
   break;
 }
 return gravity;
}

//-------------------------------------------------------------------------------------------------

void ColorTransferControl::mouseDown(std::vector <Ball>& _balls, float _mouseX, float _mouseY)
{
 for (size_t i = 0; i < _balls.size(); i++)
 {
   if (mouseBallChecker(_balls[i], _mouseX, _mouseY))
   {
     m_grabbedBall = i;
     m_cursorOffset = glm::vec2(_mouseX, _mouseY) - _balls[i].m_position;
     m_prevPosition = _balls[i].m_position;
     _balls[i].m_velocity = glm::vec2(0.0f);
   }
 }
}

//-------------------------------------------------------------------------------------------------

void ColorTransferControl::mouseUp(std::vector <Ball>& _balls)
{
 if (m_grabbedBall != -1)
 {
   _balls[m_grabbedBall].m_velocity = _balls[m_grabbedBall].m_position - m_prevPosition;
   m_grabbedBall = -1;
 }
}

//-------------------------------------------------------------------------------------------------

void ColorTransferControl::mouseMotion(std::vector <Ball>& _balls, float _mouseX, float _mouseY)
{
 if (m_grabbedBall != -1)
 {
   _balls[m_grabbedBall].m_position = glm::vec2(_mouseX, _mouseY) - m_cursorOffset;
 }
}

//-------------------------------------------------------------------------------------------------

bool ColorTransferControl::mouseBallChecker(Ball& b, float _mouseX, float _mouseY)
{
 return (_mouseX >= b.m_position.x - b.m_radius && _mouseX < b.m_position.x + b.m_radius &&
   _mouseY >= b.m_position.y - b.m_radius && _mouseY < b.m_position.y + b.m_radius);
}

//-------------------------------------------------------------------------------------------------

void ColorTransferControl::update(std::vector <Ball>& _balls, BallGrid* _ballGrid, float _deltaTime, int _maxX, int _maxY)
{
 const float FRICTION = 0.04f;
 //update balls that have been grabbed with new velocity
 //if the ball is not equal to -1 it means that we have succesfully grabbed the ball
 //this will then apply the new velocity of the ball allowing it
 //to  move through the air
 if (m_grabbedBall != -1)
 {
   //sets the throwing algorithm in place
   //this means the velocity of the ball will equal to the distance between the throw
   //if the ball new position is small the velocity will be slow if its big the velocity will be large
   _balls[m_grabbedBall].m_velocity = _balls[m_grabbedBall].m_position - m_prevPosition;

 }

 //-------------------------------------------------------------------------------------------------

 glm::vec2 gravity = getGravityMovement();

 for (size_t i = 0; i < _balls.size(); i++)
 {
   //sets a handle for better effecientcy
   Ball& ball = _balls[i];
   //update the momentum and gravity of the ball if its not grabbed
   if ((int)i != m_grabbedBall)
   {
     //if ball is not grabbes set ball position plus velocity to have the ball
     //move through screen
     ball.m_position += ball.m_velocity * _deltaTime;

     //applies friction to the balls dependent on there m_mass
     glm::vec2 movementVec = ball.m_velocity * ball.m_mass;

     //if the momvent vecotr does not equal 0 for both x and y
     //then check the friction of the balls
     if (movementVec.x != 0 || movementVec.y != 0)
     {
       if (FRICTION < glm::length(movementVec))
       {
         ball.m_velocity -= _deltaTime * FRICTION * glm::normalize(movementVec) / ball.m_mass;
       }
       else
       {
         ball.m_velocity = glm::vec2(0.0f);
       }
     }
     //apply gravity
     ball.m_velocity += gravity * _deltaTime;
   }

   //-------------------------------------------------------------------------------------------------

   //check wall collision
   if (ball.m_position.x < ball.m_radius)
   {
     ball.m_position.x = ball.m_radius;
     if (ball.m_velocity.x < 0) ball.m_velocity.x *= -1;
   }
   else if (ball.m_position.x + ball.m_radius >= _maxX)
   {
     ball.m_position.x = _maxX - ball.m_radius - 1;
     if (ball.m_velocity.x > 0) ball.m_velocity.x *= -1;
   }
   if (ball.m_position.y < ball.m_radius)
   {
     ball.m_position.y = ball.m_radius;
     if (ball.m_velocity.y < 0) ball.m_velocity.y *= -1;
   }
   else if (ball.m_position.y + ball.m_radius >= _maxY)
   {
     ball.m_position.y = _maxY - ball.m_radius - 1;
     if (ball.m_velocity.y > 0) ball.m_velocity.y *= -1;
   }

   //-------------------------------------------------------------------------------------------------

   Cell* newCell = _ballGrid->getCell(ball.m_position);
   if (newCell != ball.m_cellLeader)
   {
     //need to shift the ball
     _ballGrid->removeBall(&_balls[i]);
     _ballGrid->addBall(&_balls[i], newCell);
   }
 }

 //-------------------------------------------------------------------------------------------------

 //update all collisions
 updateCollision(_ballGrid);

 if (m_grabbedBall != -1)
 {
   _balls[m_grabbedBall].m_velocity = _balls[m_grabbedBall].m_position - m_prevPosition;
   m_prevPosition = _balls[m_grabbedBall].m_position;
 }
}

//-------------------------------------------------------------------------------------------------

void ColorTransferControl::updateCollision(BallGrid* _ballGrid)
{
 for (int i = 0; i < (int)_ballGrid->m_cells.size(); i++)
 {
   //how for into a given row is the program
   int x = i % _ballGrid->m_numCellsX;
   //how many rows do we have
   int y = i / _ballGrid->m_numCellsX;

   Cell& cell = _ballGrid->m_cells[i];

   //-------------------------------------------------------------------------------------------------

   //loop throuhg all balls in a cell
   for (int j = 0; j < (int)cell.balls.size(); j++)
   {
     Ball* ball = cell.balls[j];
     //update with residing cell
     collisionChecker(ball, cell.balls, j + 1);
     //update collision with neighbour cells
     if (x > 0)
     {
       //left
       collisionChecker(ball, _ballGrid->getCell(x - 1, y)->balls, 0);
       if (y > 0)
       {
         //top left
         collisionChecker(ball, _ballGrid->getCell(x - 1, y - 1)->balls, 0);
       }
       if (y < _ballGrid->m_numCellsY - 1)
       {
         //bottom left
         collisionChecker(ball, _ballGrid->getCell(x - 1, y + 1)->balls, 0);
       }
     }
     //up cell
     if (y > 0)
     {
       collisionChecker(ball, _ballGrid->getCell(x, y - 1)->balls, 0);
     }
   }
 }
}

//-------------------------------------------------------------------------------------------------

void ColorTransferControl::collisionChecker(Ball* _ball, std::vector<Ball*>& ballsToCheck, int startingIndex)
{
 for (int i = (int)startingIndex; i < (int)ballsToCheck.size(); i++)
 {
   collisionChecker(*_ball, *ballsToCheck[i]);
 }
}

//-------------------------------------------------------------------------------------------------

void ColorTransferControl::collisionChecker(Ball& b1, Ball& b2)
{
 glm::vec2 distVec = b2.m_position - b1.m_position;
 glm::vec2 distDir = glm::normalize(distVec);

 float distance = glm::length(distVec);
 float m_radius = b1.m_radius + b2.m_radius;

 float collisionDepth = m_radius - distance;

 //check for collision
 if (collisionDepth > 0)
 {
   b1.m_position -= distDir * collisionDepth * (b2.m_mass / b1.m_mass) * 0.5f;
   b2.m_position += distDir * collisionDepth * (b1.m_mass / b2.m_mass) * 0.5f;



   //calculate the deflection of the balls
   float aci = glm::dot(b1.m_velocity, distDir);
   float bci = glm::dot(b2.m_velocity, distDir);

   float acf = (aci * (b1.m_mass - b2.m_mass) + 2 * b2.m_mass * bci) / (b1.m_mass + b2.m_mass);
   float bcf = (bci * (b2.m_mass - b1.m_mass) + 2 * b1.m_mass * aci) / (b1.m_mass + b2.m_mass);

   b1.m_velocity += (acf - aci) * distDir;
   b2.m_velocity += (bcf - bci) * distDir;


   //Here is the transfer color code
   //gets the length of the velocity and if its greater then 0.5 allow the transfer to happen
   if (glm::length(b1.m_velocity + b2.m_velocity) > 0.5f)
   {
     //choose the faster ball if the length of the velocity for b1 is less then the
     //velocity of b2 then change the colours around
     bool change = glm::length(b1.m_velocity) < glm::length(b2.m_velocity);

     change ? b2.m_color = b1.m_color : b1.m_color = b2.m_color;
   }
 }
}













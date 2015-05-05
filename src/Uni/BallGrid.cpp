/*
 Copyright © 2015 Philip Gifford
 SDAGE 1st year 2nd PPP Assignment 2015
*/

#include "BallGrid.h"

// ---------------------------------------------------------------------------------------
/// @file BallGrid.cpp
/// @brief Implements 2D grid and stores balls in cells to allow spatial partioning
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------


BallGrid::BallGrid(int _width, int _height, int _cellSize) :
m_width(_width),
m_height(_height),
m_cellSize(_cellSize)
{
  //Divides width by cell size and chops off the end of a cell if the ball is
  //located near the side of the wall
  //Uses ceil method which prevents leaving an extra cell
  m_numCellsX = ceil((float)m_width / m_cellSize);
  m_numCellsY = ceil((float)m_height / m_cellSize);

//-------------------------------------------------------------------------------------------------

  //Whenever init the grid loop through and reserve internal vectors
  //Otherwise keep having to resize internal memory for each different cell and
  //overall improve performance by a bit

  //allocate all the cells
  const int m_radius = 20;

  //Use the formula for the area of a rectangle to create the grid to check collision
  m_cells.resize(m_numCellsY * m_numCellsX);
  for (int i = 0; i < (int)m_cells.size(); i++)
  {
    m_cells[i].balls.reserve(m_radius);
  }
}

//-------------------------------------------------------------------------------------------------

BallGrid::~BallGrid()
{
}

//-------------------------------------------------------------------------------------------------

Cell* BallGrid::getCell(int _x, int _y)
{
  //simple error checking  to bound the cells
  //if they don't match the correct values
  if (_x < 0) _x = 0;
  if (_x >= m_numCellsX) _x = m_numCellsX - 1;

  if (_y < 0) _y = 0;
  if (_y >= m_numCellsY) _y = m_numCellsY - 1;

  /////http://programmers.stackexchange.com/questions/212808/treating-a-1d-data-structure-as-2d-grid////
  //treats the 1D array as a 2D array
  //gets the area of the rectangle and finally add numCellX
  return &m_cells[_y * m_numCellsX + _x];
}

//-------------------------------------------------------------------------------------------------

Cell* BallGrid::getCell(const glm::vec2& pos)
{
  //Determine what cell the ball is in
  int cellX = (int)(pos.x / m_cellSize);
  int cellY = (int)(pos.y / m_cellSize);

  //call getCell against to error check for previous function
  return getCell(cellX, cellY);
}

//-------------------------------------------------------------------------------------------------

void BallGrid::addBall(Ball* _ball)
{
  //Determine what cell the ball exist in
  //Here I get the cell the position belongs to
  Cell* cell = getCell(_ball->m_position);

  //adds the ball to that cell and pushes it back onto the stack
  cell->balls.push_back(_ball);

  //Set ball owners cell equal to the current cell
  //this way each cell will know which one it belongs in
  _ball->m_cellLeader = cell;

  //Allows for the ball to be track through the cell index and allows for the
  //program to find position of the ball
  _ball->m_cellVectorIndex = cell->balls.size() - 1;
}

//-------------------------------------------------------------------------------------------------

void BallGrid::addBall(Ball* _ball, Cell* _cell)
{
  //Follows same steps as addBall except removes first line
  _cell->balls.push_back(_ball);
  _ball->m_cellLeader = _cell;
  _ball->m_cellVectorIndex = _cell->balls.size() - 1;
}

//-------------------------------------------------------------------------------------------------

///remove the ball from the cell
void BallGrid::removeBall(Ball* _ball)
{
  //replace ball->m_cellLeader->balls with balls
  std::vector<Ball*>& balls = _ball->m_cellLeader->balls;

  // Normal vector swap
  balls[_ball->m_cellVectorIndex] = balls.back();
  balls.pop_back();

  //since moved the ball to new position need to update the balls new position
  //update vector index
  //If ball.size is 0 then this will always be false
  if (_ball-> m_cellVectorIndex < (int)balls.size())
  {
   //update vector index
   balls[_ball->m_cellVectorIndex]->m_cellVectorIndex = _ball->m_cellVectorIndex;
  }
  //set the index of the ball to -1 this specify no longer in a vector
  _ball->m_cellVectorIndex = -1;
  _ball->m_cellLeader = 0;
}



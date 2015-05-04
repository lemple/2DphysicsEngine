
#include "BallGrid.h"


BallGrid::BallGrid(int width, int height, int cellSize) :
m_width(width),
m_height(height),
m_cellSize(cellSize)
{
  //Divides width by cell size and chops off the end of a cell if the ball is
  //located near the side of the wall
  //Uses ceil method which prevents leaving an extra cell
  m_numCellsX = ceil((float)m_width / m_cellSize);
  m_numCellsY = ceil((float)m_height / m_cellSize);


  //Whenever init the grid loop through and reserve internal vectors
  //Otherwise keep having to resize internal memory for each different cell and
  //overall improve performance by a bit

  //allocate all the cells
  const int BALLS_TO_RESERVE = 20;

  //Use the formula for the area of a rectangle to create the grid to check collision
  m_cells.resize(m_numCellsY * m_numCellsX);
  for (int i = 0; i < m_cells.size(); i++)
  {
    m_cells[i].balls.reserve(BALLS_TO_RESERVE);
  }
}

BallGrid::~BallGrid()
{
}

Cell* BallGrid::getCell(int x, int y)
{
  //simple error checking  to bound the cells
  //if they don't match the correct values
  if (x < 0) x = 0;
  if (x >= m_numCellsX) x = m_numCellsX - 1;

  if (y < 0) y = 0;
  if (y >= m_numCellsY) y = m_numCellsY - 1;

  /////http://programmers.stackexchange.com/questions/212808/treating-a-1d-data-structure-as-2d-grid////
  //treats the 1D array as a 2D array
  //gets the area of the rectangle and finally add numCellX
  return &m_cells[y * m_numCellsX + x];
}

Cell* BallGrid::getCell(const glm::vec2& pos)
{
  //Determine what cell the ball is in
  int cellX = (int)(pos.x / m_cellSize);
  int cellY = (int)(pos.y / m_cellSize);

  //call getCell against to error check for previous function
  return getCell(cellX, cellY);
}

void BallGrid::addBall(Ball* ball)
{
  //Determine what cell the ball exist in
  //Here I get the cell the position belongs to
  Cell* cell = getCell(ball->position);

  //adds the ball to that cell and pushes it back onto the stack
  cell->balls.push_back(ball);

  //Set ball owners cell equal to the current cell
  //this way each cell will know which one it belongs in
  ball->cellLeader = cell;

  //Allows for the ball to be track through the cell index and allows for the
  //program to find position of the ball
  ball->cellVectorIndex = cell->balls.size() - 1;

}

void BallGrid::addBall(Ball* ball, Cell* cell)
{
  //Follows same steps as addBall except removes first line
  cell->balls.push_back(ball);
  ball->cellLeader = cell;
  ball->cellVectorIndex = cell->balls.size() - 1;
}

///remove the ball from the cell
void BallGrid::removeBall(Ball* ball)
{
  //replace ball->cellLeader->balls with balls
  std::vector<Ball*>& balls = ball->cellLeader->balls;

  // Normal vector swap
  balls[ball->cellVectorIndex] = balls.back();
  balls.pop_back();

  //since moved the ball to new position need to update the balls new position
  //update vector index
  //If ball.size is 0 then this will always be false
  if (ball->cellVectorIndex < balls.size())
  {
   //update vector index
   balls[ball->cellVectorIndex]->cellVectorIndex = ball->cellVectorIndex;
  }
  //set the index of the ball to -1 this specify no longer in a vector
  ball->cellVectorIndex = -1;
  ball->cellLeader = NULL;
}


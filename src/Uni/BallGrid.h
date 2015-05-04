
#pragma once

#include "Ball.h"

///Inlcude vector as using vector for the list
#include <vector>


///This struct contains a list of balls
///Made a struct over class as it contains no methods and is fairly simple
struct Cell
{
  //make ball a pointer so its only a vecotr of 8 bytes
  std::vector<Ball*> balls;
};

///Has a number of balls which will be stored in cells
///To accomplish this I used a 2D grid of cells
class BallGrid
{
  //This allows ball controller to be able to access the private variables stored in Grid.h
  //While still keeping them secure and keeps encapsulatio
  friend class BallControl;
public:
  BallGrid(int width, int height, int cellSize);
  ~BallGrid();

  ///Here I overload the getCell function as each one performs a similar job

  //gets cell based on cell coordinates (ball)
  Cell* getCell(int x, int y);

  ///get cell based on position of the cell in the windowl
  Cell* getCell(const glm::vec2& pos);

  ///adds a ball and determines what cell it belongs to
  void addBall(Ball* ball);

  ///adds ball to specific cell
  void addBall(Ball* ball, Cell* cell);

  ///Removes the ball from the grid
  void removeBall(Ball* ball);




  std::vector<Cell> m_cells;
  int m_cellSize;
  int m_width;
  int m_height;
  int m_numCellsX;
  int m_numCellsY;
};


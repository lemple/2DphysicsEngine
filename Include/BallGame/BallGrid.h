/*
 Copyright © 2015 Philip Gifford
 SDAGE 1st year 2nd PPP Assignment 2015
*/


// ---------------------------------------------------------------------------------------
/// @file BallGrid.h
/// @brief Imports the grid/cells to store balls in for spatial partioning
/// @version 1.0
/// @author Philip Gifford
/// @date 02/05/15
// ---------------------------------------------------------------------------------------

#ifndef __BALLGRID_H_
#define __BALLGRID_H_

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
  /**
   * @brief BallGrid
   * @param _width
   * @param _height
   * @param _cellSize
   */
  BallGrid(int _width, int _height, int _cellSize);
  ~BallGrid();

  ///Here I overload the getCell function as each one performs a similar job

  //)
  /**
   * @brief getCell gets cell based on cell coordinates (ball
   * @param _x
   * @param _y
   * @return
   */
  Cell* getCell(int _x, int _y);

  /**
   * @brief get cell based on position of the cell in the window
   * @param pos
   * @return
   */
  Cell* getCell(const glm::vec2& _pos);

  /**
   * @brief adds a ball and determines what cell it belongs to
   * @param ball
   */
  void addBall(Ball* _ball);

  /**
   * @brief adds ball to specific cell
   * @param ball
   * @param cell
   */
  void addBall(Ball* _ball, Cell* _cell);

  /**
   * @brief removeBall allows the ability removes the ball from the grid
   * @param _ball
   */
  void removeBall(Ball* _ball);

  std::vector<Cell> m_cells;
  int m_cellSize;
  int m_width;
  int m_height;
  int m_numCellsX;
  int m_numCellsY;
};
#endif


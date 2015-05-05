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

//-------------------------------------------------------------------------------------------------

#include "Ball.h"

///Inlcude vector as using vector for the list
#include <vector>

//-------------------------------------------------------------------------------------------------


///This struct contains a list of balls
///Made a struct over class as it contains no methods and is fairly simple
struct Cell
{
  //make ball a pointer so its only a vecotr of 8 bytes
  std::vector<Ball*> balls;
};

//-------------------------------------------------------------------------------------------------

class BallGrid
{
  //This allows ball controller to be able to access the private variables stored in Grid.h
  //While still keeping them secure and keeps encapsulatio
  friend class BallControl;
public:
  /**
   * @brief BallGrid
   * Has a number of balls which will be stored in cells
   * To accomplish this I used a 2D grid of cells
   * @param _width
   *              Sets width of cell in order to cut at the end
   * @param _height
   *              Sets height of cell in order to cut at the end
   * @param _cellSize
   *              Determins the size of the cell to sotre the ball in
   */
  BallGrid(int _width, int _height, int _cellSize);
  ~BallGrid();

  //-------------------------------------------------------------------------------------------------

  ///Here I overload the getCell function as each one performs a similar job
  /**
   * @brief getCell
   * Gets cell based on cell coordinates (ball
   * @param _x
   *          Bounds the cells together
   * @param _y
   *          Bounds the cells together
   * @return Returns the area of the cell
   */
  Cell* getCell(int _x, int _y);

  //-------------------------------------------------------------------------------------------------

  /**
   * @brief getCell
   * Get cell based on position of the cell in the window
   * @param pos
   *          Gets the position of the cell depending on window size
   *
   * @return the position of the cell
   */
  Cell* getCell(const glm::vec2& _pos);

  //-------------------------------------------------------------------------------------------------

  /**
   * @brief adds a ball and determines what cell it belongs to
   * @param ball
   *            Adds ball data to see if it matches the position of the cell
   */
  void addBall(Ball* _ball);

  //-------------------------------------------------------------------------------------------------

  /**
   * @brief AddBall
   * adds ball to specific cell
   * @param ball
   *            Takes the data of the ball and adds the ball to the specific cell
   * @param cell
   *            Takes the cell info in order to include the ball
   */
  void addBall(Ball* _ball, Cell* _cell);

  //-------------------------------------------------------------------------------------------------

  /**
   * @brief removeBall
   * allows the ability removes the ball from the grid
   * @param _ball
   *            Gets the data of the ball to remove the ball from the grid
   */
  void removeBall(Ball* _ball);

  //-------------------------------------------------------------------------------------------------

  std::vector<Cell> m_cells;
  int m_cellSize;
  int m_width;
  int m_height;
  int m_numCellsX;
  int m_numCellsY;

  //-------------------------------------------------------------------------------------------------
};
#endif


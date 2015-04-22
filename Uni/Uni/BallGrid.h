#pragma once

#include "ball.h"
#include <vector>

struct Cell
{
	//make ball a pointer so its only a vecotr of 8 bytes
	std::vector<Ball*> balls;
};


class BallGrid
{
	friend class BallControl;
public:
	BallGrid(int width, int height, int cellSize);
	~BallGrid();

	//gets cell based on cell coordinates (ball)
	Cell* getCell(int x, int y);
	//get cell based on position of the cell
	Cell* getCell(const glm::vec2& pos);

	//addas a ball and determines what cell it beloongs to
	void addBall(Ball* ball);
	//adds ball to specific cell
	void addBall(Ball* ball, Cell* cell);
	void removeBall(Ball* ball);




	std::vector<Cell> m_cells;
	int m_cellSize;
	int m_width;
	int m_height;
	int m_numCellsX;
	int m_numCellsY;
};


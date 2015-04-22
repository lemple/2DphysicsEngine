
#include "BallGrid.h"


BallGrid::BallGrid(int width, int height, int cellSize) :
m_width(width),
m_height(height),
m_cellSize(cellSize)
{
	m_numCellsX = ceil((float)m_width / m_cellSize);
	m_numCellsY = ceil((float)m_height / m_cellSize);


	//allocate all the cells
	const int BALLS_TO_RESERVE = 20;
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
	if (x < 0) x = 0;
	if (x >= m_numCellsX) x = m_numCellsX - 1;

	if (y < 0) y = 0;
	if (y >= m_numCellsY) y = m_numCellsY - 1;

	//treats the 1D array as a 2D array
	return &m_cells[y * m_numCellsX + x];
}

Cell* BallGrid::getCell(const glm::vec2& pos)
{

	int cellX = (int)(pos.x / m_cellSize);
	int cellY = (int)(pos.y / m_cellSize);

	return getCell(cellX, cellY);
}

void BallGrid::addBall(Ball* ball)
{
	Cell* cell = getCell(ball->position);
	cell->balls.push_back(ball);

	ball->cellLeader = cell;
	ball->cellVectorIndex = cell->balls.size() - 1;

}

void BallGrid::addBall(Ball* ball, Cell* cell)
{
	cell->balls.push_back(ball);

	ball->cellLeader = cell;
	ball->cellVectorIndex = cell->balls.size() - 1;
}

void BallGrid::removeBall(Ball* ball)
{
	std::vector<Ball*>& balls = ball->cellLeader->balls;
	// Normal vector swap
	balls[ball->cellVectorIndex] = balls.back();
	balls.pop_back();
	//upadate vector index
	if (ball->cellVectorIndex < balls.size())
	{
		balls[ball->cellVectorIndex]->cellVectorIndex = ball->cellVectorIndex;
	}
	// setn the index of the ball to -1
	ball->cellVectorIndex = -1;
	ball->cellLeader = nullptr;
}


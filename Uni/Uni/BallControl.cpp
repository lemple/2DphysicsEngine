#include "BallControl.h"
#include "ballGrid.h"

void BallControl::update(std::vector <Ball>& balls, BallGrid* ballGrid, float deltaTime, int maxX, int maxY)
{
	const float FRICTION = 0.001f;
	//update balls that have been grabbed with new velocity
	//if the ball is not equal to -1 it means that we have succesfully grabbed the ball
	//this will then apply the new velocity of the ball allowing it
	//to  move through the air
	if (m_grabbedBall != -1)
	{
		//sets the throwing algorithm in place
		//this means the velocity of the ball will equal to the distance between the throw
		//if the ball new position is small the velocity will be slow if its big the velocity will be large
		balls[m_grabbedBall].velocity = balls[m_grabbedBall].position - m_prevPosition;

	}

	glm::vec2 gravity = getGravityMovement();


	for (size_t i = 0; i < balls.size(); i++)
	{
		//sets a handle for better effecientcy
		Ball& ball = balls[i];
		//update the momentum and gravity of the ball if its not grabbed
		if (i != m_grabbedBall)
		{
			//if ball is not grabbes set ball position plus velocity to have the ball 
			//move through screen 
			ball.position += ball.velocity * deltaTime;

			//applies friction to the balls dependent on there mass
			glm::vec2 movementVec = ball.velocity * ball.mass;

			//if the momvent vecotr does not equal 0 for both x and y
			//then check the friction of the balls
			if (movementVec.x != 0 || movementVec.y != 0)
			{
				if (FRICTION < glm::length(movementVec))
				{
					ball.velocity -= deltaTime * FRICTION * glm::normalize(movementVec) / ball.mass;
				}
				else
				{
					ball.velocity = glm::vec2(0.0f);
				}
			}
			//apply gravity
			ball.velocity += gravity * deltaTime;
		}

		//check wall collision
		if (ball.position.x < ball.radius)
		{
			ball.position.x = ball.radius;
			if (ball.velocity.x < 0) ball.velocity.x *= -1;
		}
		else if (ball.position.x + ball.radius >= maxX)
		{
			ball.position.x = maxX - ball.radius - 1;
			if (ball.velocity.x > 0) ball.velocity.x *= -1;
		}
		if (ball.position.y < ball.radius)
		{
			ball.position.y = ball.radius;
			if (ball.velocity.y < 0) ball.velocity.y *= -1;
		}
		else if (ball.position.y + ball.radius >= maxY)
		{
			ball.position.y = maxY - ball.radius - 1;
			if (ball.velocity.y > 0) ball.velocity.y *= -1;
		}

		Cell* newCell = ballGrid->getCell(ball.position);
		if (newCell != ball.cellLeader)
		{
			//need to shift the ball
			ballGrid->removeBall(&balls[i]);
			ballGrid->addBall(&balls[i], newCell);
		}
	}

	//update all collisions
	updateCollision(ballGrid);
		
	//	for (size_t j = i + 1; j < balls.size(); j++)
		//{
		//	collisionChecker(ball, balls[j]);
	//	}

	if (m_grabbedBall != -1)
	{
		balls[m_grabbedBall].velocity = balls[m_grabbedBall].position - m_prevPosition;
		m_prevPosition = balls[m_grabbedBall].position;
	}
}

glm::vec2 BallControl::getGravityMovement()
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
	}
	return gravity;
}

void BallControl::mouseDown(std::vector <Ball>& balls, float mouseX, float mouseY)
{
	for (size_t i = 0; i < balls.size(); i++)
	{
		if (mouseBallChecker(balls[i], mouseX, mouseY))
		{
			m_grabbedBall = i;
			m_cursorOffset = glm::vec2(mouseX, mouseY) - balls[i].position;
			m_prevPosition = balls[i].position;
			balls[i].velocity = glm::vec2(0.0f);
		}
	}

}

void BallControl::mouseUp(std::vector <Ball>& balls)
{
	if (m_grabbedBall != -1)
	{
		//throw the ball kronk
		balls[m_grabbedBall].velocity = balls[m_grabbedBall].position - m_prevPosition;
		m_grabbedBall = -1;
	}
}

void BallControl::mouseMotion(std::vector <Ball>& balls, float mouseX, float mouseY)
{
	if (m_grabbedBall != -1)
	{
		balls[m_grabbedBall].position = glm::vec2(mouseX, mouseY) - m_cursorOffset;
	}
}

bool BallControl::mouseBallChecker(Ball& b, float mouseX, float mouseY)
{
	return (mouseX >= b.position.x - b.radius && mouseX < b.position.x + b.radius &&
			mouseY >= b.position.y - b.radius && mouseY < b.position.y + b.radius);
}


void BallControl::updateCollision(BallGrid* ballGrid)
{
	for (int i = 0; i < ballGrid->m_cells.size(); i++)
	{
		//how for into a given row is the program
		int x = i % ballGrid->m_numCellsX;
		//how many rows do we have
		int y = i / ballGrid->m_numCellsX;

		Cell& cell = ballGrid->m_cells[i];

		//loop throuhg all balls in a cell
		for (int j = 0; j < cell.balls.size(); j++)
		{
			Ball* ball = cell.balls[j];
			//update with residing cell
			collisionChecker(ball, cell.balls, j + 1);
			//update collision with neighbour cells
			if (x > 0)
			{
				//left
				collisionChecker(ball, ballGrid->getCell(x - 1, y)->balls, 0);
				if (y > 0)
				{
					//top left
					collisionChecker(ball, ballGrid->getCell(x - 1, y - 1)->balls, 0);
				}
				if (y < ballGrid->m_numCellsY - 1)
				{
					//bottom left
					collisionChecker(ball, ballGrid->getCell(x - 1, y + 1)->balls, 0);
				}	
			}
			//up cell
			if (y > 0)
			{
				collisionChecker(ball, ballGrid->getCell(x, y - 1)->balls, 0);
			}	
		}
	}
}


void BallControl::collisionChecker(Ball* ball, std::vector<Ball*>& ballsToCheck, int startingIndex)
{
	for (int i = startingIndex; i < ballsToCheck.size(); i++)
	{
		collisionChecker(*ball, *ballsToCheck[i]);
	}
}


//deals wioth collision detection for the balls
void BallControl::collisionChecker(Ball& b1, Ball& b2)
{
	glm::vec2 distVec = b2.position - b1.position;
	glm::vec2 distDir = glm::normalize(distVec);

	float distance = glm::length(distVec);
	float radius = b1.radius + b2.radius;

	float collisionDepth = radius - distance;

	//check for collision
	if (collisionDepth > 0)
	{
		b1.position -= distDir * collisionDepth * (b2.mass / b1.mass) * 0.5f;
		b2.position += distDir * collisionDepth * (b1.mass / b2.mass) * 0.5f;

		/*//push away the smaller ones
		if (b1.mass < b2.mass)
		{
			b1.position -= distDir * collisionDepth;
		}
		else
		{
			b2.position += distDir * collisionDepth;
		}
		*/

		//calculate the deflection of the balls
		float aci = glm::dot(b1.velocity, distDir);
		float bci = glm::dot(b2.velocity, distDir);

		float acf = (aci * (b1.mass - b2.mass) + 2 * b2.mass * bci) / (b1.mass + b2.mass);
		float bcf = (bci * (b2.mass - b1.mass) + 2 * b1.mass * aci) / (b1.mass + b2.mass);

		b1.velocity += (acf - aci) * distDir;
		b2.velocity += (bcf - bci) * distDir;


	}
}





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
	}
	return gravity;
}

void ColorTransferControl::mouseDown(std::vector <Ball>& balls, float mouseX, float mouseY)
{
	for (size_t i = 0; i < balls.size(); i++)
	{
		if (mouseBallChecker(balls[i], mouseX, mouseY))
		{
			m_grabbedBall = i;
			m_cursorOffset = glm::vec2(mouseX, mouseY) - balls[i].position;
			m_prevPosition = balls[i].position;
			balls[i].velocity = glm::vec2(0.0f);
		}
	}

}

void ColorTransferControl::mouseUp(std::vector <Ball>& balls)
{
	if (m_grabbedBall != -1)
	{
		//throw the ball kronk
		balls[m_grabbedBall].velocity = balls[m_grabbedBall].position - m_prevPosition;
		m_grabbedBall = -1;
	}
}

void ColorTransferControl::mouseMotion(std::vector <Ball>& balls, float mouseX, float mouseY)
{
	if (m_grabbedBall != -1)
	{
		balls[m_grabbedBall].position = glm::vec2(mouseX, mouseY) - m_cursorOffset;
	}
}

bool ColorTransferControl::mouseBallChecker(Ball& b, float mouseX, float mouseY)
{
	return (mouseX >= b.position.x - b.radius && mouseX < b.position.x + b.radius &&
		mouseY >= b.position.y - b.radius && mouseY < b.position.y + b.radius);
}


void ColorTransferControl::update(std::vector <Ball>& balls, BallGrid* ballGrid, float deltaTime, int maxX, int maxY)
{
	const float FRICTION = 0.001f;
	//update balls that have been grabbed with new velocity
	//if the ball is not equal to -1 it means that we have succesfully grabbed the ball
	//this will then apply the new velocity of the ball allowing it
	//to  move through the air
	if (m_grabbedBall != -1)
	{
		//sets the throwing algorithm in place
		//this means the velocity of the ball will equal to the distance between the throw
		//if the ball new position is small the velocity will be slow if its big the velocity will be large
		balls[m_grabbedBall].velocity = balls[m_grabbedBall].position - m_prevPosition;

	}

	glm::vec2 gravity = getGravityMovement();


	for (size_t i = 0; i < balls.size(); i++)
	{
		//sets a handle for better effecientcy
		Ball& ball = balls[i];
		//update the momentum and gravity of the ball if its not grabbed
		if (i != m_grabbedBall)
		{
			//if ball is not grabbes set ball position plus velocity to have the ball 
			//move through screen 
			ball.position += ball.velocity * deltaTime;

			//applies friction to the balls dependent on there mass
			glm::vec2 movementVec = ball.velocity * ball.mass;

			//if the momvent vecotr does not equal 0 for both x and y
			//then check the friction of the balls
			if (movementVec.x != 0 || movementVec.y != 0)
			{
				if (FRICTION < glm::length(movementVec))
				{
					ball.velocity -= deltaTime * FRICTION * glm::normalize(movementVec) / ball.mass;
				}
				else
				{
					ball.velocity = glm::vec2(0.0f);
				}
			}
			//apply gravity
			ball.velocity += gravity * deltaTime;
		}

		//check wall collision
		if (ball.position.x < ball.radius)
		{
			ball.position.x = ball.radius;
			if (ball.velocity.x < 0) ball.velocity.x *= -1;
		}
		else if (ball.position.x + ball.radius >= maxX)
		{
			ball.position.x = maxX - ball.radius - 1;
			if (ball.velocity.x > 0) ball.velocity.x *= -1;
		}
		if (ball.position.y < ball.radius)
		{
			ball.position.y = ball.radius;
			if (ball.velocity.y < 0) ball.velocity.y *= -1;
		}
		else if (ball.position.y + ball.radius >= maxY)
		{
			ball.position.y = maxY - ball.radius - 1;
			if (ball.velocity.y > 0) ball.velocity.y *= -1;
		}

		Cell* newCell = ballGrid->getCell(ball.position);
		if (newCell != ball.cellLeader)
		{
			//need to shift the ball
			ballGrid->removeBall(&balls[i]);
			ballGrid->addBall(&balls[i], newCell);
		}
	}

	//update all collisions
	updateCollision(ballGrid);

	//	for (size_t j = i + 1; j < balls.size(); j++)
	//{
	//	collisionChecker(ball, balls[j]);
	//	}

	if (m_grabbedBall != -1)
	{
		balls[m_grabbedBall].velocity = balls[m_grabbedBall].position - m_prevPosition;
		m_prevPosition = balls[m_grabbedBall].position;
	}
}

void ColorTransferControl::updateCollision(BallGrid* ballGrid)
{
	for (int i = 0; i < ballGrid->m_cells.size(); i++)
	{
		//how for into a given row is the program
		int x = i % ballGrid->m_numCellsX;
		//how many rows do we have
		int y = i / ballGrid->m_numCellsX;

		Cell& cell = ballGrid->m_cells[i];

		//loop throuhg all balls in a cell
		for (int j = 0; j < cell.balls.size(); j++)
		{
			Ball* ball = cell.balls[j];
			//update with residing cell
			collisionChecker(ball, cell.balls, j + 1);
			//update collision with neighbour cells
			if (x > 0)
			{
				//left
				collisionChecker(ball, ballGrid->getCell(x - 1, y)->balls, 0);
				if (y > 0)
				{
					//top left
					collisionChecker(ball, ballGrid->getCell(x - 1, y - 1)->balls, 0);
				}
				if (y < ballGrid->m_numCellsY - 1)
				{
					//bottom left
					collisionChecker(ball, ballGrid->getCell(x - 1, y + 1)->balls, 0);
				}
			}
			//up cell
			if (y > 0)
			{
				collisionChecker(ball, ballGrid->getCell(x, y - 1)->balls, 0);
			}
		}
	}
}

void ColorTransferControl::collisionChecker(Ball* ball, std::vector<Ball*>& ballsToCheck, int startingIndex)
{
	for (int i = startingIndex; i < ballsToCheck.size(); i++)
	{
		collisionChecker(*ball, *ballsToCheck[i]);
	}
}

void ColorTransferControl::collisionChecker(Ball& b1, Ball& b2)
{
	glm::vec2 distVec = b2.position - b1.position;
	glm::vec2 distDir = glm::normalize(distVec);

	float distance = glm::length(distVec);
	float radius = b1.radius + b2.radius;

	float collisionDepth = radius - distance;

	//check for collision
	if (collisionDepth > 0)
	{
		b1.position -= distDir * collisionDepth * (b2.mass / b1.mass) * 0.5f;
		b2.position += distDir * collisionDepth * (b1.mass / b2.mass) * 0.5f;

		/*//push away the smaller ones
		if (b1.mass < b2.mass)
		{
		b1.position -= distDir * collisionDepth;
		}
		else
		{
		b2.position += distDir * collisionDepth;
		}
		*/

		//calculate the deflection of the balls
		float aci = glm::dot(b1.velocity, distDir);
		float bci = glm::dot(b2.velocity, distDir);

		float acf = (aci * (b1.mass - b2.mass) + 2 * b2.mass * bci) / (b1.mass + b2.mass);
		float bcf = (bci * (b2.mass - b1.mass) + 2 * b1.mass * aci) / (b1.mass + b2.mass);

		b1.velocity += (acf - aci) * distDir;
		b2.velocity += (bcf - bci) * distDir;

		if (glm::length(b1.velocity + b2.velocity) > 0.5f)
		{
			//choose the fatser ball
			bool change = glm::length(b1.velocity) < glm::length(b2.velocity);

			change ? b2.color = b1.color : b1.color = b2.color;
		}
	}
}





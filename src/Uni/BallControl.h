#pragma once
#include <vector>
#include "Ball.h"

enum class GravityControl { NONE, LEFT, UP, RIGHT, DOWN };

class BallGrid;


//implements the logic for the balls and allows them to be controlled
class BallControl
{
public:
	//update the balls. Sotre the balls in a vector so each one can have a diffrentl value
	//void update(std::vector <Ball>& balls, BallGrid* ballGrid,  float deltaTime, int maxX, int maxY);
	virtual void update(std::vector <Ball>& balls, BallGrid* ballGrid, float deltaTime, int maxX, int maxY);

	void setGravityDirection(GravityControl dir) { m_gravityControl = dir; }

	//event functions for mouse control
//	bool mouseBallChecker(Ball& b, float mouseX, float mouseY);
	//void mouseDown(std::vector <Ball>& balls, float mouseX, float mouseY);
//	void mouseUp(std::vector <Ball>& balls);
	//void mouseMotion(std::vector <Ball>& balls, float mouseX, float mouseY);

	virtual bool mouseBallChecker(Ball& b, float mouseX, float mouseY);
	virtual void mouseDown(std::vector <Ball>& balls, float mouseX, float mouseY);
	virtual void mouseUp(std::vector <Ball>& balls);
	virtual void mouseMotion(std::vector <Ball>& balls, float mouseX, float mouseY);
	virtual void updateCollision(BallGrid* ballGrid);
	virtual void collisionChecker(Ball* ball, std::vector<Ball*>& ballsToCheck, int startingIndex);
	//checks collision between two balls
	virtual void collisionChecker(Ball& b1, Ball& b2);

	glm::vec2 getGravityMovement();

	//give the grabbed ball an index of -1 to be registerd in the vector of balls
	int m_grabbedBall = -1;

	glm::vec2 m_prevPosition = glm::vec2(0.0f);
	glm::vec2 m_cursorOffset = glm::vec2(0.0f);

	GravityControl m_gravityControl = GravityControl::NONE;

private:
	//bool mouseBallChecker(Ball& b, float mouseX, float mouseY);
//	void updateCollision(BallGrid* ballGrid);
	//checks collision between a ball and a vector of balls statring at a specifci index
	//void collisionChecker(Ball* ball, std::vector<Ball*>& ballsToCheck, int startingIndex);
	//checks collision between two balls
	// void collisionChecker( Ball& b1, Ball& b2);
	

	
//	glm::vec2 getGravityMovement();

	//give the grabbed ball an index of -1 to be registerd in the vector of balls
	//int m_grabbedBall = -1;

	//glm::vec2 m_prevPosition = glm::vec2(0.0f);
//	glm::vec2 m_cursorOffset = glm::vec2(0.0f);

	//GravityControl m_gravityControl = GravityControl::NONE;

};

class ColorTransferControl : public BallControl
{
public:
	glm::vec2 getGravityMovement();

	virtual bool mouseBallChecker(Ball& b, float mouseX, float mouseY);
	virtual void mouseDown(std::vector <Ball>& balls, float mouseX, float mouseY);
	virtual void mouseUp(std::vector <Ball>& balls);
	virtual void mouseMotion(std::vector <Ball>& balls, float mouseX, float mouseY);

	virtual void update(std::vector <Ball>& balls, BallGrid* ballGrid, float deltaTime, int maxX, int maxY);
	virtual void updateCollision(BallGrid* ballGrid) override;
	virtual void collisionChecker(Ball* ball, std::vector<Ball*>& ballsToCheck, int startingIndex) override;
	virtual void collisionChecker(Ball& b1, Ball& b2) override;


};

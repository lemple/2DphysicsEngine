#pragma once
#include <Randini/Camera2D.h>
#include <Randini/SpriteLoader.h>
#include <Randini/InputControl.h>
#include <Randini/Window.h>
#include <Randini/GLSLProgram.h>
#include <Randini/Timer.h>
#include <memory>

#include "BallControl.h"
#include "BallRenderer.h"
#include "BallGrid.h"

enum class GameState
{
	PLAY,
	EXIT
};

const int CELL_SIZE = 12;




class MainGame
{
public:
	~MainGame();
	void run();

private:

	void initSystems();

	void gameLoop();

	void initRenderers();

	void initControllers();

	void update(float deltaTime);

	void drawGame();

	void initBalls();

	void drawHud();

	void processInput();


	int _screenWidth = 0, _screenHeight = 0;
	int m_currentRenderer = 0;
	int m_currentController = 0;
	std::vector<Ball> _ball;

	//BallControl m_ballControl;
	//BallRenderer m_ballRenderer;

	std::vector<BallRenderer*> m_ballRenderers;
	std::vector<BallControl*> m_ballControllers;

	//grid of spatial partioning
	std::unique_ptr<BallGrid> m_ballGrid;


	Randini::Window m_window;
	Randini::SpriteLoader m_spriteLoader;
	Randini::Camera2D m_camera;
	Randini::InputControl m_inputControl;
	Randini::GLSLProgram m_textureProgram;
	Randini::FPSLimiter m_fpsLimiter;
	
	float m_fps = 0.0f;

	GameState _gameState = GameState::PLAY;


};


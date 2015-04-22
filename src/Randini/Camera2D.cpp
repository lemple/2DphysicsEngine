#include "Camera2D.h"

namespace Randini
{
	//inits the private varibles
	Camera2D::Camera2D() :
		_position(0.0f, 0.0f),
		_cameraMatrix(1.0f),
		_orthoMatrix(1.0f),
		_scale(1.0f),
		_matrixChange(true),
		_screenHeight(500),
		_screenWidth(500)
	{

	}


	Camera2D::~Camera2D()
	{

	}
	//only needs to update camera if it needs to 
	void Camera2D::updateCamera()
	{
		//only updates the camera matrix if the program need to
		if (_matrixChange)
		{
			//encodes the translation
			//parameters: pos x, y and z, 
			glm::vec3 translate(-_position.x + _screenWidth / 2, -_position.y + _screenHeight / 2, 0.0f);
			//translates the entire viewport and make it so if I move the camera to the left everything moves to the right
			_cameraMatrix = glm::translate(_orthoMatrix, translate);

			//for scaling the camera matrix 
			//paramters: x position and y and o for z
			glm::vec3 scale(_scale, _scale, 0.0f);
		
			_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * _cameraMatrix;
			//whenever we need a camera matrix set it to false
			_matrixChange = false;
		}

	}

	glm::vec2 Camera2D::getWorldScreenCoords(glm::vec2 screenCoords)
	{
		//invert y coords
		screenCoords.y = _screenHeight - screenCoords.y;

		//make it so 0 is the center by dividing widht and height by 2
		screenCoords -= glm::vec2(_screenWidth / 2, _screenHeight / 2);
		//scale the coordinates in case we're zoomed in really far or out
		screenCoords /= _scale;
		//translate with the camera position dependent on where clicking is
		screenCoords += _position;
		return screenCoords;
	}


	void Camera2D::init(int screenWidth, int screenHeight)
	{
		//set the varibles for the init function
		_screenWidth = screenWidth;
		_screenHeight = screenHeight;
		//gets the orthogrpahic projection matrix
		//glm ortho will build the program a matrix
		//parameters will be: left side of the window, screenWidth and since it has to be a flaot declare it
		_orthoMatrix = glm::ortho(0.0f, (float)_screenWidth, 0.0f, (float)_screenHeight);
	}
}
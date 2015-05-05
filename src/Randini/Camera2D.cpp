/*
 Copyright © 2015 Philip Gifford
 SDAGE 1st year 2nd PPP Assignment 2015
*/


#include "Camera2D.h"

// ---------------------------------------------------------------------------------------
/// @file Camera2D.cpp
/// @brief Implements the camera and retrives the screen coordinates
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------

namespace Randini
{
	//inits the private varibles
	Camera2D::Camera2D() :
    m_position(0.0f, 0.0f),
    m_cameraMatrix(1.0f),
    m_orthoMatrix(1.0f),
    m_scale(1.0f),
    m_matrixChange(true),
    m_screenHeight(500),
    m_screenWidth(500)
	{

	}


	Camera2D::~Camera2D()
	{

	}

  void Camera2D::init(int _screenWidth, int _screenHeight)
  {
    //set the varibles for the init function
    m_screenWidth = _screenWidth;
    m_screenHeight = _screenHeight;
    //gets the orthogrpahic projection matrix
    //glm ortho will build the program a matrix
    //parameters will be: left side of the window, screenWidth and since it has to be a flaot declare it
    m_orthoMatrix = glm::ortho(0.0f, (float)m_screenWidth, 0.0f, (float)m_screenHeight);
  }

	//only needs to update camera if it needs to 
	void Camera2D::updateCamera()
	{
		//only updates the camera matrix if the program need to
    if (m_matrixChange)
		{
			//encodes the translation
			//parameters: pos x, y and z, 
      glm::vec3 translate(-m_position.x + m_screenWidth / 2, -m_position.y + m_screenHeight / 2, 0.0f);
			//translates the entire viewport and make it so if I move the camera to the left everything moves to the right
      m_cameraMatrix = glm::translate(m_orthoMatrix, translate);

			//for scaling the camera matrix 
			//paramters: x position and y and o for z
      glm::vec3 scale(m_scale, m_scale, 0.0f);
		
      m_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * m_cameraMatrix;
			//whenever we need a camera matrix set it to false
      m_matrixChange = false;
		}

	}

	glm::vec2 Camera2D::getWorldScreenCoords(glm::vec2 screenCoords)
	{
		//invert y coords
    screenCoords.y = m_screenHeight - screenCoords.y;

		//make it so 0 is the center by dividing widht and height by 2
    screenCoords -= glm::vec2(m_screenWidth / 2, m_screenHeight / 2);
		//scale the coordinates in case we're zoomed in really far or out
    screenCoords /= m_scale;
		//translate with the camera position dependent on where clicking is
    screenCoords += m_position;
		return screenCoords;
	}
}


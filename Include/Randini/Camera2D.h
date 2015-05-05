/*
 Copyright © 2015 Philip Gifford
 SDAGE 1st year 2nd PPP Assignment 2015
*/


// ---------------------------------------------------------------------------------------
/// @file Camera2D.h
/// @brief Creates the camera gains screen coordinates and returns the camera position
/// @version 1.0
/// @author Philip Gifford
/// @date 02/05/15
// ---------------------------------------------------------------------------------------
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Randini
{
	//makes the camera
	class Camera2D
	{
	public:
    Camera2D();
		~Camera2D();

		//init the camera needs to pass in screenWidht and height 

    /**
     * @brief init
     * @param _screenWidth
     * @param _screenHeight
     */
    void init(int _screenWidth, int _screenHeight);

    /**
     * @brief updateCamera
     */
		void updateCamera();

		//this takes the screen coordinates convert to the world cooridnates and returns the value
		glm::vec2 getWorldScreenCoords(glm::vec2 screenCoords);

		//setter function to set the position of the camera to the new position
		//pass it in by reference so I don't have to copy two floats

    /**
     * @brief setPosition
     * @param newPosition
     */
		void setPosition(const glm::vec2& newPosition)
		{
      m_position = newPosition;
      m_matrixChange = true;
		}

		//a get function to retrive the location of the scale	
		glm::vec2 getPosition()
		{
      return m_position;
		}


    /**
     * @brief setScale
     * ability to zoom in or out of the screen
     * simple settrer function to set the scale of the camera
     * @param newScale
     */
		void setScale(float newScale)
		{
      m_scale = newScale;
      m_matrixChange = true;
		}

		//a get function to retrive the location of the scale	
		float getScale()
		{
      return m_scale;
		}
		//every time we update we change the current camera matrix if the user commands it
		//onlyu need to alter this if the scale or position changes
		glm::mat4 getCameraMatrix()
		{
      return m_cameraMatrix;
		}

	private:
		//used to get the viewport dimensnions and tell them to the init screen function
    int m_screenWidth, m_screenHeight;

		//need to make a bool function in case the user wishes to change the camer matrix
		//the varibles only need to change if the math changes
    bool m_matrixChange;
    float m_scale;
		//sets the private position varible. 
		//makes two floates with the glm libary 
    glm::vec2 m_position;
		//used to set the structure of the matrix
		//mat 4 contructs a 4x4 matrix
    glm::mat4 m_cameraMatrix;
		//stores the orthoprojection matriix
    glm::mat4 m_orthoMatrix;
	};

}

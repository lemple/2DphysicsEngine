#pragma once
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
		void init(int _screenWidth, int _screenHeight);


		void updateCamera();

		//this takes the screen coordinates convert to the world cooridnates and returns the value
		glm::vec2 getWorldScreenCoords(glm::vec2 screenCoords);



		//setter function to set the position of the camera to the new position
		//pass it in by reference so I don't have to copy two floats
		void setPosition(const glm::vec2& newPosition)
		{
			_position = newPosition; 
			_matrixChange = true;
		}

		//a get function to retrive the location of the scale	
		glm::vec2 getPosition()
		{
			return _position;
		}

		//ability to zoom in or out of the screen
		//simple settrer function to set the scale of the camera
		void setScale(float newScale)
		{
			_scale = newScale;
			_matrixChange = true;
		}

		//a get function to retrive the location of the scale	
		float getScale()
		{
			return _scale;
		}
		//every time we update we change the current camera matrix if the user commands it
		//onlyu need to alter this if the scale or position changes
		glm::mat4 getCameraMatrix()
		{
			return _cameraMatrix;
		}

	private:
		//used to get the viewport dimensnions and tell them to the init screen function
		int _screenWidth, _screenHeight;

		//need to make a bool function in case the user wishes to change the camer matrix
		//the varibles only need to change if the math changes
		bool _matrixChange;
		float _scale;
		//sets the private position varible. 
		//makes two floates with the glm libary 
		glm::vec2 _position;
		//used to set the structure of the matrix
		//mat 4 contructs a 4x4 matrix
		glm::mat4 _cameraMatrix;
		//stores the orthoprojection matriix
		glm::mat4 _orthoMatrix;
	};

}
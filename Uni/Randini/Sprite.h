/*#pragma once

//using vertex buffer method rather then immediate mode on the fixed pipeline
//as this means I can store alll vertices in an array and simply call a draw function

#include <GL/glew.h>
#include "GLTexture.h"
#include <string>

namespace Randini
{
	class Sprite
	{
	public:
		Sprite(void);
		~Sprite(void);

		//function used to initilise the function
		//varibles passed in are the dimensions for the sprites as well as the path
		//to find the file that contains the texture
		//use string to get the file name
		void init(float x, float y, float width, float height, std::string texturePath);

		//function used to draw the sprites
		void draw();

	private:
		//general varibles used to get the dimensions of the sprite
		//and the  texture
		float _x;
		float _y;
		float _width;
		float _height;
		//make a GLuint for the vertex buffer ID
		//tells openLG which vertex buffer I want to draw and it takes the pointer
		//GLuint means its guaranteed to be 32bits
		GLuint _vboID;
		GLTexture _texture;

	};

}
*/
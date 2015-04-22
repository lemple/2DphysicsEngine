#pragma once
#include <GL/glew.h>

//openGL texture
namespace Randini
{
	struct GLTexture
	{
		//make is for the id of the texture
		//as wellll as width and height to know the properties of the textures
		GLuint id;
		int width;
		int height;
	};
}
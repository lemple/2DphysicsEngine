#pragma once
#include "GLTexture.h"
#include <string>
//I made this class a static class as there only needs to be one instance of the class
//so therefore there is no need in making the class anything else.
namespace Randini
{
	class ImageLoader
	{
	public:
		//make a function that returns a GLTexture
		//the only parameter the function needs is the file path name which uses a string
		static GLTexture loadPNG(std::string filePath);

	};
}

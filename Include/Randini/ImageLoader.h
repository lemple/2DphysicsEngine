/*
 Copyright © 2015 Philip Gifford
 SDAGE 1st year 2nd PPP Assignment 2015
*/


// ---------------------------------------------------------------------------------------
/// @file ImageLoader.h
/// @brief Reads a texture file and returns a GLTexture
/// @version 1.0
/// @author Philip Gifford
/// @date 02/05/15
// ---------------------------------------------------------------------------------------

#include "GLTexture.h"
#include <string>

//-------------------------------------------------------------------------------------------------

//I made this class a static class as there only needs to be one instance of the class
//so therefore there is no need in making the class anything else.
namespace Randini
{

	class ImageLoader
	{
	public:
    /**
     * @brief loadPNG
     * make a function that returns a GLTexture
     * the only parameter the function needs is the file path name which uses a string
     * @param filePath
     *          Retrives the filePath on where to find the textures
     * @return
     *          the filePath of the texture
     */
		static GLTexture loadPNG(std::string filePath);

	};
}

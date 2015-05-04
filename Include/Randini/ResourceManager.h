/*
 Copyright © 2015 Philip Gifford
 SDAGE 1st year 2nd PPP Assignment 2015
*/


// ---------------------------------------------------------------------------------------
/// @file ResourceManager.h
/// @brief Calls texturecache to retrieve texture path
/// @version 1.0
/// @author Philip Gifford
/// @date 02/05/15
// ---------------------------------------------------------------------------------------

#include "TextureCache.h"
#include <string>

//make a static class as it only needs to   as it only needs to work with one instance of the texture chache
namespace Randini
{
	class ResourceManager
	{
	public:
		//wrapper function
		//follows the same priciples as the texture chace and calls it
		static GLTexture getTexture(std::string texturePath);

	private:
		static TextureCache _textureCache;
	};

}

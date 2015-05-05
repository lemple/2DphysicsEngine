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

//-------------------------------------------------------------------------------------------------

//make a static class as it only needs to   as it only needs to work with one instance of the texture chache
namespace Randini
{
	class ResourceManager
	{
	public:

    /**
     * @brief getTexture
     * follows the same priciples as the texture chace and calls it
     *
     * @param texturePath
     *            Gets the texture path from the texturecache
     * @return
     *            Texturepath of the texture from the texturecache
     */
		static GLTexture getTexture(std::string texturePath);

    //-------------------------------------------------------------------------------------------------

	private:

    static TextureCache m_textureCache;
	};

}

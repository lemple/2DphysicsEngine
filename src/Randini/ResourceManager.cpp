/*
 Copyright © 2015 Philip Gifford
 SDAGE 1st year 2nd PPP Assignment 2015
*/

#include "ResourceManager.h"

// ---------------------------------------------------------------------------------------
/// @file ResourceManager.cpp
/// @brief Calls texture chache in order to retrive texture path
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------


namespace Randini
{

  TextureCache ResourceManager::m_textureCache;

	//calls the texture chache 
	GLTexture ResourceManager::getTexture(std::string texturePath)
	{
    return m_textureCache.getTexture(texturePath);
	}
}

/*
 Copyright © 2015 Philip Gifford
 SDAGE 1st year 2nd PPP Assignment 2015
*/

#include "TextureCache.h"
#include "ImageLoader.h"
#include <iostream>

// ---------------------------------------------------------------------------------------
/// @file TextureCache.cpp
/// @brief Check if texture is in texture path and creates if there isnt
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------

namespace Randini
{
	TextureCache::TextureCache()
	{
	}

  //-------------------------------------------------------------------------------------------------


	TextureCache::~TextureCache()
	{
	}

  //-------------------------------------------------------------------------------------------------

	GLTexture TextureCache::getTexture(std::string texturePath)
	{
		//looks up the texture and sees if its in the map
		//auto set for std::map<std::string, GLTexture>::iterator
    auto mit = m_textureMap.find(texturePath);

    //-------------------------------------------------------------------------------------------------

		//check if the texture is not in the map
    if (mit == m_textureMap.end())
		{
			//load a png file for the texture and return a texture
			GLTexture newTexture = ImageLoader::loadPNG(texturePath);

			//insert it into the map
      //inserts a new pair and use make_pair which creates a new path
			//paramters: current texture path and the new addedtexture to the program 
      m_textureMap.insert(make_pair(texturePath, newTexture));

			//return the newTexture thats been created
			return newTexture;
		}

    //-------------------------------------------------------------------------------------------------

    //since mit is not pointing to texturemap.end it is pointing to the texture
    //Therefore return mit to the second pair which will return the texture
		return mit->second;


	}
}

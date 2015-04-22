#include "TextureCache.h"
#include "ImageLoader.h"
#include <iostream>

namespace Randini
{
	TextureCache::TextureCache()
	{
	}


	TextureCache::~TextureCache()
	{
	}

	GLTexture TextureCache::getTexture(std::string texturePath)
	{
		//looks up the texture and sees if its in the map
		//auto set for std::map<std::string, GLTexture>::iterator
		auto mit = _textureMap.find(texturePath);

		//check if the texture is not in the map
		if (mit == _textureMap.end())
		{
			//load a png file for the texture and return a texture
			GLTexture newTexture = ImageLoader::loadPNG(texturePath);

			//insert it into the map
			//inserts a new pair and use make_pait which creates a new path
			//paramters: current texture path and the new addedtexture to the program 
			_textureMap.insert(make_pair(texturePath, newTexture));

		//	std::cout << "Loaded Texture!\n";

			//return the newTexture thats been created
			return newTexture;
		}
	//	std::cout << "Loaded Cached Texture!\n";
		//since mit is not pointing to texturemap.end it is pointing to the texture that the program wants
		//so return mit to the second pair which will return the texture
		return mit->second;


	}
}

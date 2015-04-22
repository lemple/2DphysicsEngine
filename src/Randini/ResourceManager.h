#pragma once
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

		//static GLuint _boundTexture;


	private:
		static TextureCache _textureCache;
	};

}
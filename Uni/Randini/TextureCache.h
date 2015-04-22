#pragma once
#include <map>
#include "GLTexture.h"

namespace Randini
{
	class TextureCache
	{
	public:
		TextureCache();
		~TextureCache();

		//returns GLTexture. look up in the map and see if the texture is there
		//if it is then it will just return the existing texture 
		//the texture internally stores the GLuint ID which is a pointer to the actual texture
		//if it dosent create a new which will push it back onto the texture map.
		GLTexture getTexture(std::string texturePath);


	private:
		//takes two elements. first element is the filepath and the name
		std::map<std::string, GLTexture> _textureMap;


	};

}
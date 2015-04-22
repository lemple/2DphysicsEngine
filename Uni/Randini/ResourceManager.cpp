#include "ResourceManager.h"


namespace Randini
{

	TextureCache ResourceManager::_textureCache;

	//calls the texture chache 
	GLTexture ResourceManager::getTexture(std::string texturePath)
	{
		return _textureCache.getTexture(texturePath);

	}
}
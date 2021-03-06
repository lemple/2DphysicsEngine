/*
 Copyright © 2015 Philip Gifford
 SDAGE 1st year 2nd PPP Assignment 2015
*/


// ---------------------------------------------------------------------------------------
/// @file TextureCache.h
/// @brief Checks if texture is in texture map, loads new textures and creates new path. Returns new texture
/// @version 1.0
/// @author Philip Gifford
/// @date 02/05/15
// ---------------------------------------------------------------------------------------

#include <map>
#include <string>
#include "GLTexture.h"

namespace Randini
{
	class TextureCache
	{
	public:
		TextureCache();
		~TextureCache();



    /**
     * @brief getTexture
     * returns GLTexture. Look up in the map and see if the texture is there
     * if it is then it will just return the existing texture
     * the texture internally stores the GLuint ID which is a pointer to the actual texture
     * if it dosent create a new which will push it back onto the texture map.
     *
     * @param texturePath
     *          Gets the texturepath from the texturemap and adds it if its not there
     *
     *
     * @return
     *        //since mit is not pointing to texturemap.end it is pointing to the texture
     *         //Therefore return mit to the second pair which will return the texture
     */
		GLTexture getTexture(std::string texturePath);

    //-------------------------------------------------------------------------------------------------

	private:
		//takes two elements. first element is the filepath and the name
    std::map<std::string, GLTexture> m_textureMap;
	};}

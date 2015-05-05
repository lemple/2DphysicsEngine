/*
 Copyright © 2015 Philip Gifford
 SDAGE 1st year 2nd PPP Assignment 2015
*/

// ---------------------------------------------------------------------------------------
/// @file GLTexture.h
/// @brief Creats a struct to handle data id of textures
/// @version 1.0
/// @author Philip Gifford
/// @date 02/05/15
// ---------------------------------------------------------------------------------------

#ifndef __GLTEXTURE_H_
#define __GLTEXTURE_H_

#include <GL/glew.h>

//openGL texture
namespace Randini
{
  /**
   * @brief The GLTexture struct
   * make is for the id of the texture
   * as well as width and height to know the properties of the texture
   */
	struct GLTexture
	{

    GLuint id;
		int width;
		int height;
  };
}
#endif

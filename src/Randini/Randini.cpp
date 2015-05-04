/*
 Copyright © 2015 Philip Gifford
 SDAGE 1st year 2nd PPP Assignment 2015
*/

// ---------------------------------------------------------------------------------------
/// @file Randini.cpp
/// @brief Encapsulates program in namespace and inits everything
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------

#include <SDL/SDL.h>
#include <GL/glew.h>

#include "Randini.h"
//set namespace for Randini game engine
//encapuslates all the funtions and varibles ina  anmescope to prevent overlap
namespace Randini
{

	int init()
	{
    //This initilises SDL and sets up everything it needs to run.
		//Give it the flags "everything" just to ensure I have no init erros later 
		SDL_Init(SDL_INIT_EVERYTHING);

		//tells SDL to double buffer so we don't get any flickering
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		return 0;
	}

}

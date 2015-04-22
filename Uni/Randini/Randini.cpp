
#include <SDL/SDL.h>
#include <GL/glew.h>

#include "Randini.h"
//set namespace for Randini game engine
//encapuslates all the funtions and varibles ina  anmescope to prevent overlap and allows me to understand what libary its from
namespace Randini
{

	int init()
	{
		//This initilises SLD and sets up everything it needs to run.
		//Give it the flags "everything" just to ensure I have no init erros later 
		SDL_Init(SDL_INIT_EVERYTHING);

		//tells SDL to double buffer so we don't get any flickering
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		return 0;
	}

}
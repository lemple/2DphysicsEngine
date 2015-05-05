/*
 Copyright © 2015 Philip Gifford
 SDAGE 1st year 2nd PPP Assignment 2015
*/

#include "Window.h"
#include "Errors.h"

// ---------------------------------------------------------------------------------------
/// @file Window.cpp
/// @brief Creates the window and allows handles to be manipulated
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------

namespace Randini
{
	Window::Window()
	{
	}


	Window::~Window()
	{
	}

	int Window::create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags)
	{
		//set the flags to be with window openGL so that I still have a openGL screen
		Uint32 flags = SDL_WINDOW_OPENGL;

		//check to see if flag is set to hidden
		if (currentFlags & HIDDEN)
		{
			// |= mean or equals because you keep forgetting phil
			//if flag is set to hidden sets the flag to hidden
			flags |= SDL_WINDOW_HIDDEN;
		}

		//check to see if flag is set to FULLSCREEN
		if (currentFlags & FULLSCREEN)
		{
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}
		//check to see if flag is set to BORDERLESS
		if (currentFlags & BORDERLESS)
		{
			flags |= SDL_WINDOW_BORDERLESS;
		}

		//opens up SDL window for the gameEngine.
		//this deals with all the operating systems and allows the program to run on Windows Mac etc
		//The main job of this is to return a pointer to a window. If I succesfulkly create a window then the pointer will be valid
		//If it fails it will return a nullptr
		//first I set the window variable equal to SDL_CreateWindow. In the argument list we pass in the parameters from the create function
		//The reason for this is so anyone adding a new game will be able to set new values for each argument giving them control
		//In this case the arguments passed are the window name, the position of the screen for x and y, screenWidth, height and then any flags such as fullscreen etc
    m_sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);
		//If the window does not return a pointer we call the fatal error class. This iverall helps with debugging!
    if (m_sdlWindow == NULL)
		{
			fatalError("SDL Window could not be created");
		}
		//gives the context to the window
		//bounds the context to the window and links it with _window varible
		//overall sets og the GL context and gives it to the window
    SDL_GLContext glContext = SDL_GL_CreateContext(m_sdlWindow);
    if (glContext == NULL)
		{
			fatalError("SDL_GL_context could not be created");
		}
		//inits GLEW libary returns and fatal error if it can't find the libarys
		//overall gets the extensions for the programs
		//in the error we call a #define that is in the glew libary
		GLenum error = glewInit();
		if (error != GLEW_OK)
		{
			fatalError("Could not initialize GLEW");
		}

		//checks opengl version and prints it out to consol
		std::printf("***opengl version: %s ***", glGetString(GL_VERSION));

		
		//glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

		//this function swaps the interval of the current openGL context and overall
		//sets Vsync
		SDL_GL_SetSwapInterval(0);

		//enable alpha blending to prevent the black backgorund from the PNG's
		glEnable(GL_BLEND);
		//tell the program what blending is chosen. 
		//png's incode alpha
		//paramters: source factor on how the program will effect the source colour by multiplying during the colour calulation
		//this means the colour will be multiplied by the alpha,
		// destination factor for what portion of the colour to draw on when the alpha is one it will disreguard the colors
		//when its 0 all of the colours will show through
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		return 0;
	}


	void Window::swapBuffers()
	{
		//swap the buffers of the window to prevent flickering
    SDL_GL_SwapWindow(m_sdlWindow);

	}
}

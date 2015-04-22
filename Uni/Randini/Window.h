#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <string>

namespace Randini
{

	//setting flags for the game when its created
	//hidden for hiuding the window, fullscreen for fullscreen and bordeless
	//need each one to represent a certain bit
	enum WindowFlags { HIDDEN = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };

	class Window
	{
	public:
		Window();
		~Window();

		//create window function that overall generates the windwo
		//define the handlews for the window in the parameters
		//use std::string so we can set a windowName to .c_str which will allow us to set the name
		//of the window in another project when linking the engine
		//other varibles are set so that they can be changed when I start up a new project
		int create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags);

		//function to swap the buffers around each frame to prevetn flickering
		void swapBuffers();

		//get functions used to recieve input from the varibles _screenWidth and _screenHeight
		//this includes the screen width and height 
		int getScreenWidth() { _screenWidth; }
		int getScreenHeight() { _screenHeight; }
	private:
		//creates the SDL_windows for my game engine and allows me to set up the window that can be called in any other new project/solution
		//This creates a private varible which holds the handles to determin the screen basic operations. 
		//I used a pointer as thats what the SDL create window fucntion returns 
		SDL_Window* _sdlWindow;
		//make 2 variables that contain the size of the screen width and height these will work as handles
		int _screenWidth, _screenHeight;
	};

}
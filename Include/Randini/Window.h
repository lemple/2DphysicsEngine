/*
 Copyright © 2015 Philip Gifford
 SDAGE 1st year 2nd PPP Assignment 2015
*/


// ---------------------------------------------------------------------------------------
/// @file Window.h
/// @brief Creates the genral SDL handles for settign a window, Swaps buffers and assigns window flags
/// @version 1.0
/// @author Philip Gifford
/// @date 02/05/15
// ---------------------------------------------------------------------------------------

#ifndef __WINDOW_H_
#define __WINDOW_H_

#include <SDL2/SDL.h>
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



    /**
     * @brief create
     * create window function that overall generates the windwo
     * define the handlews for the window in the parameters
     * use std::string so we can set a windowName to .c_str which will allow us to set the name
     * of the window in another project when linking the engine
     * other varibles are set so that they can be changed when I start up a new project
     *
     * @param windowName
     * @param screenWidth
     * @param screenHeight
     * @param currentFlags
     * @return
     */
		int create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags);

		//function to swap the buffers around each frame to prevetn flickering
    /**
     * @brief swapBuffers
     */
		void swapBuffers();


    /**
   * @brief getScreenWidth
   * get functions used to recieve input from the varibles m_screenWidth and m_screenHeight
   * this includes the screen width and height
   * @return the resolution of the screen
   */
  int getScreenWidth() { return m_screenWidth; }
  int getScreenHeight() { return m_screenHeight; }
	private:
		//creates the SDL_windows for my game engine and allows me to set up the window that can be called in any other new project/solution
		//This creates a private varible which holds the handles to determin the screen basic operations. 
		//I used a pointer as thats what the SDL create window fucntion returns 
    SDL_Window* m_sdlWindow;
		//make 2 variables that contain the size of the screen width and height these will work as handles
    int m_screenWidth, m_screenHeight;
	};

}
#endif

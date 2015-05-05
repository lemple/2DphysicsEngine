/*
 Copyright © 2015 Philip Gifford
 SDAGE 1st year 2nd PPP Assignment 2015
*/

#include "Timer.h"

#include <SDL2/SDL.h>

// ---------------------------------------------------------------------------------------
/// @file Timer.cpp
/// @brief Calculates FPS and ticks then procceeds to cap it at 60
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------

namespace Randini
{
	
	FPSLimiter::FPSLimiter()
	{

	}

	void FPSLimiter::init(float maxFPS)
	{
		setMaxFPS(maxFPS);
	}

	void FPSLimiter::begin()
	{
    m_startTicks = SDL_GetTicks();
	}

	
	float FPSLimiter::end()
	{
		calculateFPS();

    float frameTicks = SDL_GetTicks() - m_startTicks;

		//limit fps to max fps by dividing 1000m/s by maxFPS and producing m/f
    if (1000.0f / m_maxFPS > frameTicks)
		{
			//force the frame to delay by diffrence between desired frametime minus the actual frametime
      SDL_Delay(1000.0f / m_maxFPS - frameTicks);
		}
		//return FPS
    return m_fps;
	}

	void FPSLimiter::setMaxFPS(float maxFPS)
	{
    m_maxFPS = maxFPS;
	}

	void FPSLimiter::calculateFPS()
	{
		//making them static as I want them to retain there state until they are called again
		//number of frames the progrma will average
		static const int NUM_SAMPLES = 10;
		static float frameTimes[NUM_SAMPLES];
		static int currentFrame = 0;

		//used to retain the previous ticks and uses geticks which retrives the data of ticks 
		//need previous ticks in order to calculate the frame time
		static float prevTicks = SDL_GetTicks();
		//monitors the current frameticks
		float currentTicks;
		currentTicks = SDL_GetTicks();

		//work out the frametime by minusing the currenticks from the previoous ticks
    m_frameTime = currentTicks - prevTicks;
		//way to make sure the frameTiume is going through a circle of currentFrame is by
		//using modulo and gives the remainder which will equal to frametime and will keep through a circle
    frameTimes[currentFrame % NUM_SAMPLES] = m_frameTime;

		prevTicks = currentTicks;

		//number the progrma will average of FPS
		int count;

		currentFrame++;

		//if currentFrame is less then num_samples then only do currentFrame average
		if (currentFrame < NUM_SAMPLES)
		{
			count = currentFrame;
		}
		else
			//if beyond the first 3 frames then continue
		{
			count = NUM_SAMPLES;
		}

		//gets running average of number of frames
		float frameTimeAverage = 0;
		for (int i = 0; i < count; i++)
		{
			frameTimeAverage += frameTimes[i];
		}
		//actually average the frameTime
		frameTimeAverage /= count;

		//ensure that the program is not dividing by 0
		if (frameTimeAverage > 0)
		{
			//1000 m/s divided by the frameTimeaverage  
      m_fps = 1000.0f / frameTimeAverage;
		}
		else
		{
      m_fps = 60.0f;
		}
	}

}

#include "Timer.h"

#include <SDL/SDL.h>


namespace Randini
{
	
	FPSLimiter::FPSLimiter()
	{

	}

	//calls fps lmiter so it can be called for other games
	void FPSLimiter::init(float maxFPS)
	{
		setMaxFPS(maxFPS);
	}

	void FPSLimiter::begin()
	{
		_startTicks = SDL_GetTicks();
	}

	
	float FPSLimiter::end()
	{
		calculateFPS();

		float frameTicks = SDL_GetTicks() - _startTicks;

		//limit fps to max fps by dividing 1000m/s by maxFPS and producing m/f
		if (1000.0f / _maxFPS > frameTicks)
		{
			//force the frame to delay by diffrence between desired frametime minus the actual frametime
			SDL_Delay(1000.0f / _maxFPS - frameTicks);
		}
		//return FPS
		return _fps;
	}

	//sets maxFPS for framerate
	void FPSLimiter::setMaxFPS(float maxFPS)
	{
		_maxFPS = maxFPS;
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
		_frameTime = currentTicks - prevTicks;
		//way to make sure the frameTiume is going through a circle of currentFrame is by
		//using modulo and gives the remainder which will equal to frametime and will keep through a circle
		frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

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
			_fps = 1000.0f / frameTimeAverage;
		}
		else
		{
			_fps = 60.0f;
		}
	}

}

/*
 Copyright © 2015 Philip Gifford
 SDAGE 1st year 2nd PPP Assignment 2015
*/


// ---------------------------------------------------------------------------------------
/// @file Timer.h
/// @brief Calculates, monitors, and caps the FPS this allows for setting deltaTime later
/// @version 1.0
/// @author Philip Gifford
/// @date 02/05/15
// ---------------------------------------------------------------------------------------

#ifndef __TIMER_H_
#define __TIMER_H_

namespace Randini
{
	class FPSLimiter
	{
	public:
		FPSLimiter();

		void init(float maxFPS);

		void setMaxFPS(float maxFPS);

		void begin();

		//limits the FPS to 60
		//and returns the FPS
		float end();
	private:
		void calculateFPS();

		//general varibles for FPS functions
		float _fps;
		float _frameTime;
		float _maxFPS;

		//sets the start of the FPS whenever begin is called
		unsigned int _startTicks;
	};
}
#endif

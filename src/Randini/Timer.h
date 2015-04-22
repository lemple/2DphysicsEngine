#pragma once

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
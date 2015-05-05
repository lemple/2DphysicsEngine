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

//-------------------------------------------------------------------------------------------------

namespace Randini
{
	class FPSLimiter
	{
	public:
		FPSLimiter();

    /**
     * @brief init
     * calls fps lmiter so it can be called for other games
     *
     * @param maxFPS
     *        Inits the maxFPS to the maxFPS
     */
		void init(float maxFPS);

    //-------------------------------------------------------------------------------------------------

    /**
     * @brief setMaxFPS
     * sets maxFPS for framerate to 60FPS
     * @param maxFPS
     *          Calculates and sets the maxFPS to 60
     */
		void setMaxFPS(float maxFPS);

    //-------------------------------------------------------------------------------------------------

    /**
     * @brief begin
     * Begins the ticks
     */
		void begin();

    //-------------------------------------------------------------------------------------------------

    /**
     * @brief end
     * Limits the fps and forces a slight delay for the fps
     * (Seeing the delay only applys if you print FPS to consol)
     * And end the ticking
     * @return The FPS
     */
    float end();

    //-------------------------------------------------------------------------------------------------

	private:

    /**
     * @brief calculateFPS
     * Calculates the FPS compared to the running time of the program
     * This will output hig fs due to the small nature of the program
     * However can set an average and overall recienve a lower framerate
     */
		void calculateFPS();

    //-------------------------------------------------------------------------------------------------

		//general varibles for FPS functions
    float m_fps;
    float m_frameTime;
    float m_maxFPS;

    //-------------------------------------------------------------------------------------------------

		//sets the start of the FPS whenever begin is called
    unsigned int m_startTicks;
	};
}
#endif

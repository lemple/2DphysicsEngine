/*
 Copyright © 2015 Philip Gifford
 SDAGE 1st year 2nd PPP Assignment 2015
*/


// ---------------------------------------------------------------------------------------
/// @file inputControl.h
/// @brief Stores SDL_Keys to key map and sets mouse coordinates
/// @version 1.0
/// @author Philip Gifford
/// @date 02/05/15
// ---------------------------------------------------------------------------------------

#include <glm/glm.hpp>

#include <map>

//-------------------------------------------------------------------------------------------------

typedef std::map<unsigned int, bool> KeyPair;

namespace Randini
{
   /**
   * @brief The InputControl class
   * Overall stores a key map which maps SDL_Keys to bools
   * If the value is true this means the key has been pressed
   * Anything else means the key has been released
   *
   */
	class InputControl
	{
	public:
		InputControl();
		~InputControl();

    //-------------------------------------------------------------------------------------------------

    /**
     * @brief update
     * function to update the key when it is pressed
     */
		void update();

    //-------------------------------------------------------------------------------------------------

    /**
     * @brief pressKey
     * function to deal	when a key is pressed
     * store the ID as a unsinged int
     * @param keyID
     *          Check to see if the keyID is in the map returns true if so
     *
     */
		void pressKey(unsigned int keyID);

    //-------------------------------------------------------------------------------------------------

    /**
     * @brief releaseKey
     * Deals with when a key is released
     *
     * @param keyID
     *          Follows same method as pressKey but checks if its set to false
     */
		void releaseKey(unsigned int keyID);

    //-------------------------------------------------------------------------------------------------

    /**
     * @brief setMouseCoords
     * Gets the cursors corrdinates so they can be used for camera movment etc
     *
     * @param x
     *        Sets the mouse coords equal to x axis
     * @param y
     *        Sets the mouse coords equal to y axis
     */
		void setMouseCoords(float x, float y);

    //-------------------------------------------------------------------------------------------------
		
    /**
     * @brief isKeyDown
     * returns true if key is down
     *
     * @param keyID
     *          Check to see if key is in map if not then program won't insert it
     * @return 2
     *          Returns false if key is not down &
     *          Returns it->secodn which means it found the key in the map
     *
     */
		bool isKeyDown(unsigned int keyID);

    //-------------------------------------------------------------------------------------------------

    /**
     * @brief isKeyPressed
     * returns true if key was just pressed
     * @param keyID
     * @return
     *         Returns Treu if it was
     *         Returns false if it wasent
     *
     */
		bool isKeyPressed(unsigned int keyID);

    //-------------------------------------------------------------------------------------------------

		//makes a gett function for the mouse coordinates to get the mouses coordinates
		glm::vec2 getMouseCoords() const
		{
      return m_mouseCoords;
		}

    //-------------------------------------------------------------------------------------------------

	private:

    /**
     * @brief wasKeyDown
     * made private as it will only be enternally used by is key pressed and therefore adds security
     * returns true if key is down
     *
     * @param keyID
     *         Checks the keyID to see if the key was pressed down
     * @return
     *         Returns false if key is not down &
     *         Returns it->secodn which means it found the key in the map
     */
		bool wasKeyDown(unsigned int keyID);

    //-------------------------------------------------------------------------------------------------

		//using unordered map as it works faster then a map container as it need to access
		//individual elements since it stores it as a hash table rather then a tree
		//This method uses up more space but works faster and since its a small engine this is not an issue
    KeyPair m_keyMap;
    KeyPair m_previousKeyMap;
		//gets the mouse coordinates for shooting
    glm::vec2 m_mouseCoords;
	};

}

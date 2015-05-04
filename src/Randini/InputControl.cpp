/*
 Copyright © 2015 Philip Gifford
 SDAGE 1st year 2nd PPP Assignment 2015
*/

#include "InputControl.h"

// ---------------------------------------------------------------------------------------
/// @file InputControl.cpp
/// @brief Stores SDL_keys in keymap creating smoother controls
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------

// Input manager stores a key map that maps SDL_Keys to bools
// If the value in the key map is true, then the key is pressed
// Otherwise, it is released this will improve the smoothness of the controls
//and stops them from feeling clunky
namespace Randini
{
	InputControl::InputControl() : _mouseCoords(0.0f)
	{
	}


	InputControl::~InputControl()
	{
	}

	void InputControl::update()
	{
		//  Loops through _keyMap using a for each loop and copy it over to _previousKeyMap
//    for(auto& it : _keyMap)
    for( KeyPair::const_iterator key = _keyMap.begin();
         key != _keyMap.end();
         key++)
		{
      _previousKeyMap[(*key).first] = (*key).second;
		}
	}

	void InputControl::pressKey(unsigned int keyID)
	{
		//treat key map like an array and set equal to true
		//first checks to see if keyID is in the map if its not
		//it will create it and set it to true
		_keyMap[keyID] = true;
	}

	void InputControl::releaseKey(unsigned int keyID)
	{
		//follow same scenario as presskey except set to false
		_keyMap[keyID] = false;
	}

	
	void InputControl::setMouseCoords(float x, float y)
	{
		//Sets the mouseCoord equal to x and y to define the 
		//x and y values
		_mouseCoords.x = x;
		_mouseCoords.y = y;

	}

	bool InputControl::isKeyDown(unsigned int keyID)
	{
		//check manually to see if its in the map 
		//if its not in the map then the program won't insert it and
		//return false
		//use auto for std::unordered_map<unsigned int, bool>
		//look for keyID
		auto it = _keyMap.find(keyID);
		//checks to see if keyID is found
		if (it != _keyMap.end())
		{
			return it->second;
		}
		else
		{
			return false;
		}
	}

	bool InputControl::isKeyPressed(unsigned int keyID)
	{
		//check if it is pressed this frame and wasent pressed last frame
		if (isKeyDown(keyID) == true && wasKeyDown(keyID) == false)
		{
			return true;
		}
		return false;
	}

	bool InputControl::wasKeyDown(unsigned int keyID)
	{
		
		auto it = _previousKeyMap.find(keyID);
		if (it != _previousKeyMap.end())
		{
			return it->second;
		}
		else
		{
			return false;
		}
	}
}


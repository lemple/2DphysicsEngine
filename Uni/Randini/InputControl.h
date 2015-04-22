#pragma once
#include <glm/glm.hpp>

#include <unordered_map>

namespace Randini
{
	class InputControl
	{
	public:
		InputControl();
		~InputControl();

		//Overall stores a key map which maps SDL_Keys to bools
		//If the value is true this means the key has been pressed
		//Anything else means the key has been released

		//function to update the key when it is pressed
		void update();
		//function to deal	when a key is pressed	
		//store the ID as a unsinged int
		void pressKey(unsigned int keyID);
		//Deals with when a key is released
		void releaseKey(unsigned int keyID);
		//Gets the mcursors corrdinates so they can be used for camera movment etc
		void setMouseCoords(float x, float y);
		
		/// returns true if key is down
		bool isKeyDown(unsigned int keyID);

		// returns true if key was just pressed
		bool isKeyPressed(unsigned int keyID);

		//makes a gett function for the mouse coordinates to get the mouses coordinates
		glm::vec2 getMouseCoords() const
		{
			return _mouseCoords;
		}

	private:
		//made private as it will only be enternally used by is key pressed and therefore adds security
		/// returns true if key is down
		bool wasKeyDown(unsigned int keyID);

		//using unordered map as it works faster then a map container as it need to access
		//individual elements since it stores it as a hash table rather then a tree
		//This method uses up more space but works faster and since its a small engine this is not an issue
		std::unordered_map<unsigned int, bool> _keyMap;
		std::unordered_map<unsigned int, bool> _previousKeyMap;
		//gets the mouse coordinates for shooting
		glm::vec2 _mouseCoords;
	};

}
#include "Errors.h"

#include <cstdlib>

#include <iostream>
#include <SDL2/SDL.h>

namespace Randini
{
	//sets up an error check for the engine
	//this will be used to check if certain parts of the program has not worked correctly 
	//and overall helpes with debugging
	//creates a string for the error to be stored in so when theres and error you can call the string 
	//and input the current error
	//tmp promopts the user to quit
	void fatalError(std::string errorString)
	{
		std::cout << errorString << std::endl;
		std::cout << "Enter any key to quit...";
		int tmp;
		std::cin >> tmp;
		SDL_Quit();
		exit(69);

	}
}

#pragma once
#include <string>

//sets up the function for the error
namespace Randini
{
	//use extern to tell the compiler that the for decleration is coming from a diffrent location
	extern void fatalError(std::string errorString);
}
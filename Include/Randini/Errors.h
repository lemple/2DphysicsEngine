/*
 Copyright © 2015 Philip Gifford
 SDAGE 1st year 2nd PPP Assignment 2015
*/


// ---------------------------------------------------------------------------------------
/// @file Error.h
/// @brief Creates a error cheker to retun error messages
/// @version 1.0
/// @author Philip Gifford
/// @date 02/05/15
// ---------------------------------------------------------------------------------------

#include <string>

//sets up the function for the error
namespace Randini
{
	//use extern to tell the compiler that the for decleration is coming from a diffrent location
	extern void fatalError(std::string errorString);
}

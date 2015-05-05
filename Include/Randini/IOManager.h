/*
 Copyright © 2015 Philip Gifford
 SDAGE 1st year 2nd PPP Assignment 2015
*/


// ---------------------------------------------------------------------------------------
/// @file IOManager.h
/// @brief Seeks the size of the buffer and reads the file to it returns open file
/// @version 1.0
/// @author Philip Gifford
/// @date 02/05/15
// ---------------------------------------------------------------------------------------

#include <vector>
#include <string>

//-------------------------------------------------------------------------------------------------

//main purpose of this class is to be able to read a file into a buffer
//without having to rewrite the code everytime
//I made this class a static class as there only needs to be one instance of the class
//so therefore there is no need in making the class anything else.

namespace Randini
{
	class IOManager
	{
	public:

    /**
     * @brief readFileToBuffer
     * reads a file into the buffer.
     * parameters: pass in the buffer by reference. the way this works is the user will
     * pass in there own empty vector and the function will fill the data with the data they need.
     *
     * @param filePath
     *            Define the file path thats being passed in using vecotor.
     * @param buffer
     *            Passes in the buffer from the user so it will only fill the data it needs
     *
     * @return
     *            Returns true if the program opens the file
     */
		static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);
	};

}

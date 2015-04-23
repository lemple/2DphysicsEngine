#pragma once

#include <vector>
#include <string>

//main purpose of this class is to be able to read a file into a buffer
//wihtout having to rewrite the code everytime
//I made this class a static class as there only needs to be one instance of the class
//so therefore there is no need in making the class anything else.

namespace Randini
{
	class IOManager
	{
	public:
		//reads a file into the buffer.
		//parameters: define the varible that holds the file path thats being passed in
		//using vecotor. pass in the buffer by reference. the way this works is the user will
		//pass in there own empty vector and the function will fill the data with the data they need.
		static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);
	};

}

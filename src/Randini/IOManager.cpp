#include "IOManager.h"
#include <fstream>

namespace Randini
{
	bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer)
	{
		//use ifstream as it constructs and object thats not associated with a file
		//parameters: call the filePath varible, and use ios binary as it tell the program we are readong the file in binary data
    std::ifstream file( filePath.c_str(), std::ios::binary );
		//error check to see if the file was read
		if (file.fail())
		{
			perror(filePath.c_str());
			return false;
		}

		//now the progrma reads the entire contents of the file into the buffer
		//Assume the buffer has a size of 0
		//use seekg to find out the actual size of the buffer
		//parameters: byte off set set to 0 as the next paramter I set what the operator will be relative to,
		//take the file pointer and puts it right at the end
		file.seekg(0, std::ios::end);

		//get the file size and returns an int of how many bytes have passed
		int fileSize = file.tellg();
		//back at the begining of the file
		file.seekg(0, std::ios::beg);

		//tell the program how many bytes the file is
		//reduce the file size by any header bytes that might be present
		fileSize -= file.tellg();

		//resize the buffer to the filesize
		buffer.resize(fileSize);
		//reads a number of bytes into a buffer
		//pramters: takes an array of chars. Have to make it a char * as its just a pointer pointing to memeory. althought this a buffer of unsgined char im pretending
		//pretneding its a buffer of chars. so going to read in everything as tho it was chars to start using it as a unsgined char 
		//buffer[0] is telling the progrma to get the first element in buffers at the beggining of the memoery array
		//and say what the adress of this element is
		//how many bytes we wanner read
		file.read((char *)&(buffer[0]), fileSize);
		file.close();

		//return true since the program succcefulklyu opend the file
		return true;
	}
}


#include "ImageLoader.h"
#include "picoPNG.h"
#include "IOManager.h"
#include "Errors.h"

namespace Randini
{
	//overall outputs all the data the program needs for its textures
	GLTexture ImageLoader::loadPNG(std::string filePath)
	{
		//create a GLtexture on the stack and have it return a copy
		//since the texture its returning is only 12bytes+ its ok to make a copy of it
		//and overall won't effect the performance
		// = {} will init everything to 0
		GLTexture texture = {};

		//input for the deCodePNG
		std::vector<unsigned char> in;
		//output for the deCodePNG 
		std::vector<unsigned char> out;

		//make long int as we need 8bytes instead of 4 
		unsigned long width, height;

		//call IOManager so the program can read the file to the buffer
		//parameeters: filePath of the file thats being read in. and in which is the input for the deCodePNG 
		//finally error check to see if this fails for debugging later
		if (IOManager::readFileToBuffer(filePath, in) == false)
		{
			fatalError("Failed to laod PNG file to buffer!");
		}

		//deocdePNG fucntion returns an int error 
		//provides with error checking as well
		//paramters: pass out in son that gets filled, mass in the width and height of the sprite  
		//need to give pointer to the first element so you adress of in[0], 
		//finally size of in and the number of bytes
		int errorCode = decodePNG(out, width, height, &(in[0]), in.size());

		//error checking for so set to 0 since decodePNG returns 0 whenever theres no error
//		if (errorCode != 0)
//		{
//			//use fatal error and enter the erroCode from loadPNG but need to convert the integer into a string
//			fatalError("DecodePNG failed eith error " + std::to_string(errorCode));
//		}

		//need to generate the openGL
		//parameters: how many textures the program is using in this case one. 
		//takes a pointer to a GLuint which is the adress of texture.id 
		//this will turn id into a new unique id for that specific id
		glGenTextures(1, &(texture.id));

		//need to uplaod the data with bindTexture. 
		//parameters: The type of texture that is going to be used
		//then what texutre the program wants to bind
		glBindTexture(GL_TEXTURE_2D, texture.id);

		//now need to upload the data to 
		//takes the output data and begins to upload it to the openGL texture which gets stored in the grpahics card
		//parameters: texture type, what bitmap level, internal format thats being used, dimensions of the texture so call width and height
		//if the textures want a border set to false (0), format of the pixel data thats being used
		//type of data thats being used so unsigned, finally need a pointer to the pixel data which is 
		//adress of out which will give us the first pixel of the array 
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

		//set parameters and tell openGL about the texture and what to do with it
		//paramters: want it to affect the GL_texture, texture wrapping parameter how we want the textur to wrap on one image
		//if the borders go past the border of the texture make the program repeat the texture rather then clamp it
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//Gl mag filter deals with how it will filter the image based on theincrease of size. and set to linear
		//min deals with the oppsoite, and in this case set to mip linear as dealing with mip mapping
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		//generates the min map and tells it to link with the texture
		glGenerateMipmap(GL_TEXTURE_2D);

		//unbind the current texture
		glBindTexture(GL_TEXTURE_2D, 0);

		texture.width = width;
		texture.height = height;

		//returns the texture
		return texture;
	}
}

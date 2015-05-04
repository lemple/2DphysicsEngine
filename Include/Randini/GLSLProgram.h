/*
 Copyright © 2015 Philip Gifford
 SDAGE 1st year 2nd PPP Assignment 2015
*/


// ---------------------------------------------------------------------------------------
/// @file GLSLProgram.h
/// @brief Compiles, Links, Enables, & Disables frag and vert shaders and returns the location of the uniform
/// @version 1.0
/// @author Philip Gifford
/// @date 02/05/15
// ---------------------------------------------------------------------------------------


#ifndef __GLSLPROGRAM_H_
#define __GLSLPROGRAM_H_

#include <iostream>
#include <string>
#include <GL/glew.h>

namespace Randini
{
	class GLSLProgram
	{

	public:
		GLSLProgram();
		~GLSLProgram();

		//function compiles the shaders
		//Makes a string varible so the path name of the file can be found and can extract information from the txt document
		//overall reads the file and compiles them to a format that openGL can use
		//make string const as they are never going to change and ti prevents possible bugs
		void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);

		//link shader togehter into the final program
		void linkShader();

		
		void addAttribute(const std::string& attributeName);

		//need to ask openGL the location of the of the uniform
		//make a string to askj the name of the uniform
		GLint getUniformLocation(const std::string& uniformName);

		void use();
		void unuse();

	private:
		//counts the number of attributes that the shader has
		int _numAttributes;

		//makes it so it compiles both shaders rather then having 2 huge blocks of code 
		//restricted to vertex anf frag
		void compileShader(const std::string& filePath, GLuint id);

		//need id to hold onto the shader program 
		//overall the id for the final program
		GLuint _programID;

		//I also need id's for my individual shader programs
		//Overall this deal with the handles for the shader program
		GLuint _vertexShaderID;
		GLuint _fragmentShaderID;
	};
}

#endif

/*
 Copyright © 2015 Philip Gifford
 SDAGE 1st year 2nd PPP Assignment 2015
*/

//first create the program
//then attach the shaders to the correct shader e.g. frag and vert
//then call link program and link the shaders
#include "GLSLProgram.h"
#include "Errors.h"

#include <vector>
#include <fstream>

// ---------------------------------------------------------------------------------------
/// @file GLSLProgram.cpp
/// @brief Compiles, Links and implements shader information and retives uniform location
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------

namespace Randini
{
	//set up initialization list. It is a better way to initialize variables, since it avoids an extra copy. 
  GLSLProgram::GLSLProgram() : m_numAttributes(0), m_programID(0), m_vertexShaderID(0), m_fragmentShaderID(0)
	{

	}

  //-------------------------------------------------------------------------------------------------

	GLSLProgram::~GLSLProgram()
	{
	}

  //-------------------------------------------------------------------------------------------------

	//Compiles the shaders into a form that your GPU can understand
	//this function overall opens the file shader. reads the file shader and then finally compile the shaders
	void GLSLProgram::compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilepath)
	{
		//vertex and fragment shaders are successfully compiled in the fucntion
		//after this function its time to link the shaders together in the next function
    m_programID = glCreateProgram();


		//the vertexshader is used to shader the vertx point of and object and overall 
		//used to produce color to the objects
		//creates the vertex shader object and store its ID in GL_VERTEXT_SHADER
    m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		//if the shader returns 0 call error class
    if (m_vertexShaderID == 0)
		{
			fatalError("Vertex shader failed to be created!");
		}

		//the fragment shader is used to shader the pixel point of and object and overall 
		//used to produce a blend for the colors
		//creates the fragment shader object and store its ID in GL_FRAGMENT_SHADER
    m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    if (m_fragmentShaderID == 0)
		{
			fatalError("Fragment shader failed to be created!");
		}

		//Calls each function and compiles each shader
		//pass the varible for the file path and then the ID of the shader
    compileShader(vertexShaderFilePath, m_vertexShaderID);
    compileShader(fragmentShaderFilepath, m_fragmentShaderID);
	}

  //-------------------------------------------------------------------------------------------------

	void GLSLProgram::linkShader()
	{

		//takes the shaders and attaches them to the program
		//pass in the id of the program and the type of shader and attachs them
    glAttachShader(m_programID, m_vertexShaderID);
    glAttachShader(m_programID, m_fragmentShaderID);

		//Link our program
    glLinkProgram(m_programID);

		//Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
    glGetProgramiv(m_programID, GL_LINK_STATUS, (int *)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
      glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &maxLength);

			//The maxLength includes the NULL character
			std::vector<char> errorLog(maxLength);
      glGetProgramInfoLog(m_programID, maxLength, &maxLength, &errorLog[0]);



			//since we don't need the program anymore we can delte it
      glDeleteProgram(m_programID);
			//delete the shaders to prevent memory links
      glDeleteShader(m_vertexShaderID);
      glDeleteShader(m_fragmentShaderID);

			//print the error log and quit
			std::printf("%s\n", &(errorLog[0]));
			fatalError("Shaders failed to link!");
		}

		//detach the shaders as well to prevent all chances of errors and memory leaks
    glDetachShader(m_programID, m_vertexShaderID);
    glDetachShader(m_programID, m_fragmentShaderID);
    glDeleteShader(m_vertexShaderID);
    glDeleteShader(m_fragmentShaderID);
	}

  //-------------------------------------------------------------------------------------------------

	//Adds an attribute to our shader
	//it should always be called inbetween compiling and linking 
	////binds out attributes and to tell vertex string is the first attribute
	void GLSLProgram::addAttribute(const std::string& attributeName)
	{
		//pass in the program id, then the since we have recived a attribute and increment it after it runs the function, the name will be attibuteName
    glBindAttribLocation(m_programID, m_numAttributes++, attributeName.c_str());
	}

  //-------------------------------------------------------------------------------------------------

	GLint GLSLProgram::getUniformLocation(const std::string& uniformName)
	{
		//gets the uniformas location. 
		//prameters: the id of the program we are associating the unform with which is programID.
		//then the name and use a c_str
		//use GLint location so the program can use it for error checking if the uniform can't be found
		//overall helps with debugging
    GLint location = glGetUniformLocation(m_programID, uniformName.c_str());
		//returns error if uniform can't be found
    if (location == (int)GL_INVALID_INDEX)
		{
			fatalError("Uniform " + uniformName + " Not found in shader!!");
		}
		//since the program can't return at the definition return location here
		return location;
	}

	//enable the shader and all its attributes
	void GLSLProgram::use()
	{
		//whenever we use the shader the compiler calls glUseProgram
		//pass in the programID as its the ID that the progrma is using
    glUseProgram(m_programID);
		//enable all the attributes we added with addAttribute
		//if we don't enable the attributes then the shader will be unable to use it
    for (int i = 0; i < m_numAttributes; i++)
		{
			glEnableVertexAttribArray(i);
		}
	}

  //-------------------------------------------------------------------------------------------------

	//disable the shader
	void GLSLProgram::unuse()
	{
		//since the shader has been used the program now needs to unuse the shader and delte the attributes
		glUseProgram(0);
    for (int i = 0; i < m_numAttributes; i++)
		{
			glDisableVertexAttribArray(i);
		}
	}

	//Compiles a single shader file
	void GLSLProgram::compileShader(const std::string& filePath, GLuint id)
	{

		//open the file using an ifstream
    std::ifstream shaderFile( filePath.c_str() );
		//if the file path cannot be found then return and error
		if (shaderFile.fail())
		{
			perror(filePath.c_str());
			fatalError("Failed to open " + filePath);
		}

		//Reads all the data from the file with one string
		//File contents stores all the text in the file
		std::string fileContents = "";
		//line is used to grab each line of the file
		std::string line;

		//Get all the lines in the file and add it to the contents
		//gets the line from the shader files and runs the line varible
		while (std::getline(shaderFile, line))
		{
			//concatonate strings with the +=
			fileContents += line + "\n";
		}

		//closes the file
		shaderFile.close();

		//get a pointer to our file contents c string;
		//Had to be used as I could not get around &fileContent.c_str() error
		//the reasons for this is because openGL wants an array of c strings. And since im using a normal string so I don't have an array and therefore need a poiter
		const char* contentsPtr = fileContents.c_str();
		//tell opengl that I want to use fileContents as the contents of the shader file
		//grabs the ID of the shaders, number of strings which is 1, since I have one string just pass as nullptr
    glShaderSource(id, 1, &contentsPtr, 0);

		//compile the shader and pass the id
		glCompileShader(id);

		//check for errors
		//gatherd from the GLSL page
		GLint success = 0;
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);

		if (success == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

			//The maxLength includes the NULL character
			std::vector<char> errorLog(maxLength);
			glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

			//Provide the infolog in whatever manor you deem best.
			//Exit with failure.
			//prevents shader from leaking
			glDeleteShader(id); 

			//Print error log and quit
			std::printf("%s\n", &(errorLog[0]));
			fatalError("Shader " + filePath + " failed to compile");
		}
	}
}

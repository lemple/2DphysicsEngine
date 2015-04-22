#pragma once
#include <GL/glew.h>
#include "Vertex.h"
#include <glm/glm.hpp>
#include <vector>
//allows to bunch of different sprites together in a draw call


namespace Randini
{
	//set an enum class for all the sorting types that wil be used in 
	//the sprite loader
	enum class GlyphSortType
	{
		//none for no sorting
		//sorting fron to back
		//sorting back to fron
		//and sorting by texture aso all the same texture gets drawn together 
		NONE,
		FRONT_TO_BACK,
		BACK_TO_FRONT,
		TEXTURE

	};

	//class used for depth
	//single sprite holds what type of texture and the depth
	//depth can be used for having certain sprites behind others
	class Glyph
	{
		public:
			Glyph() {};
			Glyph(const glm::vec4& destinationRect, glm::vec4& uvRect, GLuint Texture, float Depth, const ColorRGBA8& color) :
			texture(Texture), depth(Depth) {			

				//sets up the vertices for the glyph
				topLeft.color = color;
				//since its the top left it needs to be + destination.w since its the fourth element of destination rect
				topLeft.setPosition(destinationRect.x, destinationRect.y + destinationRect.w);
				//setting uv vertices
				topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

				bottomLeft.color = color;
				bottomLeft.setPosition(destinationRect.x, destinationRect.y);
				bottomLeft.setUV(uvRect.x, uvRect.y);

				topRight.color = color;
				//follow same formula as top left but add z to x position and w to y position
				topRight.setPosition(destinationRect.x + destinationRect.z, destinationRect.y + destinationRect.w);
				topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

				bottomRight.color = color;
				//since its defined on btoom left just need to add z to x position
				bottomRight.setPosition(destinationRect.x + destinationRect.z, destinationRect.y);
				bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);
			}
			//stores the textures in a GLuint
		GLuint texture;
		//storing the float
		float depth;

		Vertex topLeft;
		Vertex bottomLeft;
		Vertex topRight;
		Vertex bottomRight;

	};

	//sotres all the information it needs to render
	class RenderLoader
	{
	public:
		//parameters: offset, number of vertices and texture. rest is initinalising the varibles
		//this sets up the renderLoader
		//by following this methood it means I can simply call the construcor and define the values in the parameters
		RenderLoader(GLuint Offset, GLuint NumVertices, GLuint Texture) : offset(Offset),
			numVertices(NumVertices), texture(Texture)
		{

		}
		GLuint offset;
		GLuint numVertices;
		GLuint texture;

	};

	class SpriteLoader
	{
	public:
		SpriteLoader();
		~SpriteLoader();

		//init sprite loader
		void init();

		//calls for whenever we are ready to call
		//sets up everything for drawing
		void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);

		//sorts the images out 
		void end();

		//calls void draw thoruhg void begin and adds the sprites to the batch and gets them ready to load
		//use glm over SDL Rect so I can import the math easier
		//makes them a const so the reference does not change
		//parametes: position stored as, uv coordinates with bottom left hand cornor and dimensions, texture sotrage, depth, finally the colour struct
		//all gonna passed by values. make it by reference to prevent copys and increase speed. Make them destination const to prevent values changing 
		void draw(const glm::vec4& destinationRect, glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color);

		//renders the sprites to the screen
		void renderLoader();

	private:
		// Creates all the needed RenderLoaders
		void createRenderLoader();
		//vertex array object is a type of object that encapsulates all of the states
		//that the progrma needs to render
		//takes a large amount of object aclass and stores then in an vertex array
		//whenever the program needs to draw the program just maeks one call
		void createVertexArray();
		//used for sorting all the glyphs
		void sortGlyphs();

		//creates functions that deals with sorting of front to back
		//takes pointers as the program is dealing with pointers from Glyph pointer
		static bool compareFrontToBack(Glyph* a, Glyph* b);
		static bool compareBackToFront(Glyph* a, Glyph* b);
		static bool compareTexture(Glyph* a, Glyph* b);

		//make a GLuint for the vertex buffer ID
		//tells openLG which vertex buffer I want to draw and it takes the pointer
		//GLuint means its guaranteed to be 32bits
		GLuint _vbo;
		GLuint _vao;

		//makes a sort type varible 
		GlyphSortType _sortType;

		//better to make a glyph pointer as the glyph struc has a lot of data inside
		//making a glyph pointer since a pointer is only 8 bytes in quantity
		//this means the program will only have to sort the pointers rahte then the glyph structs
		std::vector<Glyph*> _glyphPointers; ///< This is for sorting

		//vector of glyphs to be stored inside the spriteloader
		//each time draw is called the program will push back the new glyph
		std::vector <Glyph> _glyphs; ///< This is the actual glyphs

		//sets the renderLoader to to pass in the values
		std::vector<RenderLoader> _renderLoader;
	};
}

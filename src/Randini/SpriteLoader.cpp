/*
 Copyright © 2015 Philip Gifford
 SDAGE 1st year 2nd PPP Assignment 2015
*/

#include "SpriteLoader.h"
#include <algorithm>

// ---------------------------------------------------------------------------------------
/// @file ImageLoader.cpp
/// @brief Draws, renders, sorts glyphs and allows them to be called in one draw call
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------

namespace Randini
{
	SpriteLoader::SpriteLoader() :
          m_vbo(0),
          m_vao(0)
	{

	}


	SpriteLoader::~SpriteLoader()
	{
	}

	
	void SpriteLoader::init()
	{
		//calls create vertex array whenever init is called
		createVertexArray();
	}

	//sets the sortype value to texture as default 
	void SpriteLoader::begin(GlyphSortType sortType /* GlyphSortType::TEXTURE */)
	{
		//set up any state the program needs to begin rendering
		//runs the sorting process for the glyphs whenever begin is called using sortype function
    m_sortType = sortType;
		//clears all of the vectors to prevetn overflow
    m_renderLoader.clear();
		//clears all glyphs so the program has no memory leaks
    m_glyphs.clear();
	}

	void SpriteLoader::end()
	{
		//used to sort the glyyphs and genrate batched for the glyphs 

		//set up all pointers for faster sorting
    m_glyphPointers.resize(m_glyphs.size());
    for (int i = 0; i < m_glyphs.size(); i++)
		{
      m_glyphPointers[i] = &m_glyphs[i];
		}
		//calls sorty glyphs functions
		sortGlyphs();
		createRenderLoader();
	}

	void SpriteLoader::draw(const glm::vec4& destinationRect, glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color)
	{
    m_glyphs.emplace_back(destinationRect, uvRect, texture, depth, color);
	}

	
	void SpriteLoader::renderLoader()
	{
		
		//binds vertex attriv array
    glBindVertexArray(m_vao);

		//loops through all of the loaders
    for (int i = 0; i < m_renderLoader.size(); i++)
		{
			//binds the textures
			//paramters: type of texture, texture that the progrma will bind
      glBindTexture(GL_TEXTURE_2D, m_renderLoader[i].texture);

			//draw the textures
			//parameters: pass in mode , the renderLoader with the offset, number of veritices
      glDrawArrays(GL_TRIANGLES, m_renderLoader[i].offset, m_renderLoader[i].numVertices);
		}

		//unbind vertex attrib array
		glBindVertexArray(0);
	}

	//loops through the array of glyphs and each glyph needs to be added to the loader
	//and if the program gets a glyph with a new texture then the program will make a new loader
	void SpriteLoader::createRenderLoader()
	{
		// Stores all vertices that are needed to upload
    // any time a new glyph is added going to pushback the vertices into the vertices
		std::vector <Vertex> vertices;
		
    // sets the size of vertices to glyph.size * 6 and allocated all
    // the memory for the vertices needed from glyphs
		// Resize the buffer to the exact size we need so the program will treat
		// it like an array
    // treating it like and array means the program can simply step though the array rather then calling push.back repeatedly
    vertices.resize(m_glyphPointers.size() * 6);

		//checks if there are any glyphs avalible
		//empty also means 0
    if (m_glyphPointers.empty()) {
			return;
		}

		//need to store the opffset since it should only be 0 at the start
		int offset = 0; // current offset
		int cv = 0; // current vertex

		//Add the first batch
		//wants to pass in a render loader object
		//use emplace back so instead of passing renderLoader and making a copy
		//The program simply just passes in the values
		//this means emplace back will create a new object in renderLoader and inits it
		
		//without having to make a copy (overall saving one line of code and increasing functionality)
    m_renderLoader.emplace_back(offset, 6, m_glyphPointers[0]->texture);
		//defines the 6 vertices and increments each one so it can move onto the next vertice
		//using th array glyphPointers 
    vertices[cv++] = m_glyphPointers[0]->topLeft;
    vertices[cv++] = m_glyphPointers[0]->bottomLeft;
    vertices[cv++] = m_glyphPointers[0]->bottomRight;
    vertices[cv++] = m_glyphPointers[0]->bottomRight;
    vertices[cv++] = m_glyphPointers[0]->topRight;
    vertices[cv++] = m_glyphPointers[0]->topLeft;
		//each time a new vertices is made add 6 too offset
		offset += 6;
		
		//need to loop through the rest of the glyphs
		//cg = currentGlyph
		//Add all the rest of the glyphs
		//and overall lets the program make a bunch of diffrent calls on the one renderLoader
    for (int cg = 1; cg < m_glyphPointers.size(); cg++) {

			// Check if this glyph can be part of the current loader
			//depending of if the texture is diffrent then it will emplace a new render loader
      if (m_glyphPointers[cg]->texture != m_glyphPointers[cg - 1]->texture) {
				// Make and emplace new loader but havge offset as offset and not 0
        m_renderLoader.emplace_back(offset, 6, m_glyphPointers[cg]->texture);
			}
			//else increase the size of the current render loader 
			else {
				//use back to send it to the last vertices in the array
				// If its part of the current loader increase numVertices by 6
        m_renderLoader.back().numVertices += 6;
			}
			//follow same routine from before
			//however instead of glyphsPointers to 0 set to currentGlyph
      vertices[cv++] = m_glyphPointers[cg]->topLeft;
      vertices[cv++] = m_glyphPointers[cg]->bottomLeft;
      vertices[cv++] = m_glyphPointers[cg]->bottomRight;
      vertices[cv++] = m_glyphPointers[cg]->bottomRight;
      vertices[cv++] = m_glyphPointers[cg]->topRight;
      vertices[cv++] = m_glyphPointers[cg]->topLeft;
			//incrementing offset by 6
			offset += 6;
		}

		// Bind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

		// Orphan the buffer since the program is using the same vertex of buffers
		//Orphaning reallocates the buffer object before it beings modifying
		//allocating its fatser then synchronization. and since nullptr is passed theres no need to sync
		//this means the old buffer will be thrown away and a new one will be given overall increasing speed
		//this makes oprhaning much more efficent.
		//uploads the vertex buffer data
		//use dynamic draw as the data store contents will be modified repeatedly and used many times.
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), NULL, GL_DYNAMIC_DRAW);
		// Upload a range of data 
		//paramters: where the uplaod will be, the size, and finaslly the data
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

		// Unbind the VBO
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	//type of object that encapuslates all of the state that we need to do to render openGL
	void SpriteLoader::createVertexArray()
	{
		//generates the vertex array object if the vertex array object is equal to 0 generate vertacies
		//paramters: how many is being passed in and what vertexarray we want to call
    if (m_vao == 0)
		{
      glGenVertexArrays(1, &m_vao);
		}

		//binds vertex array object meaning if the state is changed
		//it will be sotred in the vertex array object
    glBindVertexArray(m_vao);

    if (m_vbo == 0)
		{
			//generates the vertex buffer object if the vertex buffer object is equal to 0 generate vertacies
			//paramters: how many is being passed in and what vertex buffer we want to call
      glGenBuffers(1, &m_vbo);
		}
		//calls bind buffer so any time vertex array is rebinded it will also bind the buffer
		//parameters: the program the array buffer wants to use, what buffer varible
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

		//tells opengl that we want to use the first attrbute array
		//only one for the position but more later
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		//this is the postion attrubte pointer
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		//color attribute pointor
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
		//uv attrib pointer
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		//unbind vertex attribute array
		glBindVertexArray(0);
	}

	//need to sort based on what typoe of sorty type it is
	void SpriteLoader::sortGlyphs()
	{
		//uses stable sort that means two elements are the same will retin the same order 
    switch (m_sortType)
		{
		case GlyphSortType::BACK_TO_FRONT:
			//stable sort for back to front
			//praameters: takes in the interator to the begning of the container, the end of the container,
			//predicate in which passes the function to stable sort which uses the function to sort
			//overall determines what element is greater then or less then the other.
			//this deals with depth value more
      std::stable_sort(m_glyphPointers.begin(), m_glyphPointers.end(), compareBackToFront);
			break;
		case GlyphSortType::FRONT_TO_BACK:
			//praameters: takes in the interator to the begning of the container, the end of the container,
      std::stable_sort(m_glyphPointers.begin(), m_glyphPointers.end(), compareFrontToBack);
			break;
		case GlyphSortType::TEXTURE:
			//praameters: takes in the interator to the begning of the container, the end of the container,
      std::stable_sort(m_glyphPointers.begin(), m_glyphPointers.end(), compareTexture);
			break;
			
		}
	}

	//want to return true if the value of a's dpeth is less then the value of b's depth
	//this means the sorting algorithm is going to move th glyphs around in the vector
	//this means for the other fucntions I can use this method to determine what goes where
	//dending on its position in the vertex
	bool SpriteLoader::compareFrontToBack(Glyph* a, Glyph* b)
	{
		
		return (a->depth < b->depth);
	}
	bool SpriteLoader::compareBackToFront(Glyph* a, Glyph* b)
	{
		return (a->depth > b->depth);
	}
	//keeps so all textures are drawn together in one load
	//so if it has a smaller texture ID it will be drawn first
	bool SpriteLoader::compareTexture(Glyph* a, Glyph* b)
	{
		return (a->texture < b->texture);
	}
}

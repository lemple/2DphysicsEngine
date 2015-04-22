/*#include "Sprite.h"
#include "Vertex.h"
#include "ResourceManager.h"

#include <cstddef>

namespace Randini
{

	Sprite::Sprite(void)
	{
		_vboID = 0;
	}


	Sprite::~Sprite(void)
	{
	//if the id is not correct then delte the buffer ID
		if (_vboID != 0)
		{
			glDeleteBuffers(1, &_vboID);
		}
	}


	void Sprite::init(float x, float y, float width, float height, std::string texturePath)
	{
		_x = x;
		_y = y;
		_width = width;
		_height = height;

		_texture = ResourceManager::getTexture(texturePath);

		//takes vertex buffer object and assigns it to the ID of 0
		if (_vboID == 0)
		{
		//generates buffers for the vertex.
		//when we pass in vboID it generates the vboid and gives it a specific ID and overall generates the buffer
			glGenBuffers(1, &_vboID);
		}

		//makes space so the sprites can be drawn
		Vertex vertexData[6];

		//first triangle
		vertexData[0].setPosition(x + width, y + height);
		vertexData[0].setUV(1.0f, 1.0f);

		vertexData[1].setPosition(x, y + height);
		vertexData[1].setUV(0.0f, 1.0f);

		vertexData[2].setPosition(x, y);
		vertexData[2].setUV(0.0f, 0.0f);

		//second triangle
		vertexData[3].setPosition(x, y);
		vertexData[3].setUV(0.0f, 0.0f);

		vertexData[4].setPosition(x + width, y);
		vertexData[4].setUV(1.0f, 0.0f);

		vertexData[5].setPosition(x + width, y + height);
		vertexData[5].setUV(1.0f, 1.0f);

		//uploads the colors
		for (int i = 0; i < 6; i++)
		{
			vertexData[4].setColor(255, 0, 255, 255);
		}

		vertexData[4].setColor(0, 0, 255, 255);

		vertexData[4].setColor(0, 255, 0, 255);


		//adds colors for the bttom vertex to add blending



		//tells opengl to bind the vertex buffer object
		//in parammeters I tell it what type of buffer I want, and then what ID we want to pass in
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);
		//uplaod data to gpu
		//tell it to be the data size of vertex data and tells it how much data we want ot use
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

		//unbinds the buffer
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Sprite::draw()
	{
	
		//tells openGL what kind of buffer is active at the moment
		glBindTexture(GL_TEXTURE_2D, _texture.id);


		//binds the buffer object
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);

		//tells opengl that we want to use the first attrbute array
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		//this is the postion attrubte pointer
		//paramets pass in: Type of attrib array, size of vertex e.g x and y so 2 since we're dealing with 2D
		//what type which is float, if you want to normalize, how much data, aoffset value, position
		//since our position is not 0 by offset
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

		//color attribute pointor
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

		//uv attrib pointer
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		//draw 6 verttices
		glDrawArrays(GL_TRIANGLES, 0, 6);

		//disable vertex attrib array
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

}
*/
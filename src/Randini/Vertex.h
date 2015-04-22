#pragma once
#include <GL/glew.h>
//this header interleaves the vertex data 
//makes each vertex which hold colour, posisition, and shape etc


namespace Randini
{
	//having these outside means we can reuse them elsewhere
	//as they are pretty generic structs
	struct Position
	{
		float x;
		float y;
	};

	struct ColorRGBA8
	{
		ColorRGBA8() : r(0), g(0), b(0), a(0) { }
		ColorRGBA8(GLubyte R, GLubyte G, GLubyte B, GLubyte A) : 
					r(R), g(G), b(B), a(A) { }
		//4 bytes for r g b a color
		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;
	};

	struct UV
	{
		float u;
		float v;
	};

	//make small as it will cause the tranfer to the gpu quicker
	struct Vertex
	{
		//the postion struct. storing another struct insdie a struct makes composition
		//I chose trhis method as it is eaiser to read then position[2]
		Position position;

		//holds red, green, blue, and alpha
		ColorRGBA8 color;

		//set varible for texture mapping
		UV uv;

		//makes settiung the position value for the vertices easier
		void setPosition(float x, float y)
		{
			position.x = x;
			position.y = y;
		}

		/*void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
		{
			color.r = r;
			color.g = g;
			color.b = b;
			color.a = a;
		}
		*/

		//makes settiung the uv value for the vertices easier
		void setUV(float u, float v)
		{
			uv.u = u;
			uv.v = v;
		}
	};
}

#pragma once

#include <glm/glm.hpp>
#include <src/Randini/Vertex.h>

struct Cell;


//single responsibilty principle
//data for the ball

struct Ball 
{
	Ball(float radius, float mass, const glm::vec2& position, const glm::vec2& velocity, unsigned int textureId, const Randini::ColorRGBA8& color);

	float radius;
	float mass;
	glm::vec2 position;
	glm::vec2 velocity;
	unsigned int textureId = 0;
	Randini::ColorRGBA8 color;
	Cell* cellLeader = nullptr;
	int cellVectorIndex = -1;

};


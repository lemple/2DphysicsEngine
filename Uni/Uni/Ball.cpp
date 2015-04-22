#include "Ball.h"


Ball::Ball(float radius, float mass, const glm::vec2& position, const glm::vec2& velocity, unsigned int textureId, const Randini::ColorRGBA8& color)
{
	this->radius = radius;
	this->mass = mass;
	this->position = position;
	this->velocity = velocity;
	this->textureId = textureId;
	this->color = color;

}

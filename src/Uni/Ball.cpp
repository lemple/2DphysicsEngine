/*
 Copyright © 2015 Philip Gifford
 SDAGE 1st year 2nd PPP Assignment 2015
*/

#include "Ball.h"

// ---------------------------------------------------------------------------------------
/// @file Ball.cpp
/// @brief Stores the data for the balls
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------


Ball::Ball(float radius, float mass, const glm::vec2& position, const glm::vec2& velocity, unsigned int textureId, const Randini::ColorRGBA8& color)
  : textureId(0), cellVectorIndex(-1), cellLeader(NULL)
{
  this->radius = radius;
  this->mass = mass;
  this->position = position;
  this->velocity = velocity;
  this->textureId = textureId;
  this->color = color;

}

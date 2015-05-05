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


Ball::Ball(float _radius, float _mass, const glm::vec2& c_position, const glm::vec2& c_velocity, unsigned int _textureId, const Randini::ColorRGBA8& c_color)
  : m_textureId(0), m_cellVectorIndex(-1), m_cellLeader(NULL)
{
  this-> m_radius = _radius;
  this-> m_mass = _mass;
  this-> m_position = c_position;
  this-> m_velocity = c_velocity;
  this-> m_textureId = _textureId;
  this-> m_color = c_color;

}

/*
 Copyright © 2015 Philip Gifford
 SDAGE 1st year 2nd PPP Assignment 2015
*/


// ---------------------------------------------------------------------------------------
/// @file Ball.h
/// @brief Handle the data for the ball
/// @version 1.0
/// @author Philip Gifford
/// @date 02/05/15
// ---------------------------------------------------------------------------------------


#ifndef __BALL_H_
#define __BALL_H_
//Here I call GLM to assist with calling a glm::vec2
//this library will be used to help calculate the velocity of the balls
//as well as vector as we are dealing with vector positions velocity
#include <glm/glm.hpp>
#include <Include/Randini/Vertex.h>

struct Cell;


//single responsibilty principle
//data for the ball


////////////////////////////////////////////////////
//                                                //
//            PLAIN OLD DATA STRUCT               //
//                                                //
////////////////////////////////////////////////////

//contains all public variables due to the nature of the struct.

//rather then having setter or getters I found it was easier to make everything public
//As well as that a lot of the variables used are access and used outside of class and therefore
//having setters and getter in this header would be arbitrary

//main purpose of the struct is to decouple different components such as rendering/controls etc
struct Cell;


struct Ball
{
  /**
   * @brief Ball
   * This struct simply contains all the data for the ball
   *
   * @param _radius Radius of the ball
   * @param _mass Mass of the ball
   * @param c_position position of the ball
   * @param c_velocity Velocity of the ball
   * @param _textureId TextureId of the ball
   * @param c_color Color of the ball
   */
  Ball(float _radius, float _mass, const glm::vec2& c_position, const glm::vec2& c_velocity, unsigned int _textureId, const Randini::ColorRGBA8& c_color);

  float m_radius;
  float m_mass;
  glm::vec2 m_position;
  glm::vec2 m_velocity;
  unsigned int m_textureId;
  Randini::ColorRGBA8 m_color;
  Cell* m_cellLeader;

  //Here make the cell vector index which allows for me to keep track
  //of the cell through the vector
  int m_cellVectorIndex;

};
#endif



#pragma once

//Here I call GLM to assist with calling a glm::vec2
//this library will be used to help calculate the velocity of the balls
//as well as vector as we are dealing with vector positions velocity
#include <glm/glm.hpp>
#include <src/Randini/Vertex.h>

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

//This struct simply contains all the data for the ball
//Parameters: Radius of the ball, mass of the ball, position of the ball, velocity of the ball,
//textureID of the ball to apply textures, color of the balls to alter the texture.

struct Ball
{
  Ball(float radius, float mass, const glm::vec2& position, const glm::vec2& velocity, unsigned int textureId, const Randini::ColorRGBA8& color);

  float radius;
  float mass;
  glm::vec2 position;
  glm::vec2 velocity;
  unsigned int textureId;
  Randini::ColorRGBA8 color;
  Cell* cellLeader;
  //Here make the cell vector index which allows for me to keep track
  //of the cell through the vector
  int cellVectorIndex;

};


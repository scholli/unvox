//******************************************************************************
// Module: UnVox
// Author: Sebastian Thiele / Andre Schollmeyer
// 
// Copyright 2019 
// All rights reserved
//******************************************************************************
#include "gl/primitives/plane.hpp"

#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <gl/error.hpp>

namespace unvox { namespace gl {

///////////////////////////////////////////////////////////////////////////////
plane::plane(GLint vertexattrib_index, GLint normalattrib_index, GLint texcoordattrib_index)
  : _vao      (),
    _vertices ( 4 * sizeof(glm::vec4) ),
    _normals  ( 4 * sizeof(glm::vec4) ),
    _texcoords( 4 * sizeof(glm::vec4) )
{  
  size      ( 2.0f, 2.0f );

  texcoords ( glm::vec4(0.0, 0.0, 0.0, 0.0),
              glm::vec4(1.0, 0.0, 0.0, 0.0),
              glm::vec4(1.0, 1.0, 0.0, 0.0),
              glm::vec4(0.0, 1.0, 0.0, 0.0));

  normal ( glm::vec4(0.0, 0.0, 1.0, 0.0));
  attrib_location (vertexattrib_index, normalattrib_index, texcoordattrib_index);
}

///////////////////////////////////////////////////////////////////////////////
plane::~plane()
{}

///////////////////////////////////////////////////////////////////////////////
void      
plane::size ( float width, float height )
{
  // xy-plane
  std::vector<glm::vec4> vertices;
  vertices.push_back(glm::vec4( -width/2.0f, -height/2.0f,  0.0, 1.0));
  vertices.push_back(glm::vec4(  width/2.0f, -height/2.0f,  0.0, 1.0));
  vertices.push_back(glm::vec4(  width/2.0f,  height/2.0f,  0.0, 1.0));
  vertices.push_back(glm::vec4( -width/2.0f,  height/2.0f,  0.0, 1.0));

  _vertices.buffersubdata (0, unsigned( vertices.size() * sizeof(glm::vec4)),  &vertices.front());
}

///////////////////////////////////////////////////////////////////////////////
void      
plane::texcoords (glm::vec4 const& a, 
                  glm::vec4 const& b, 
                  glm::vec4 const& c, 
                  glm::vec4 const& d)
{
  std::vector<glm::vec4> tmp(4);

  tmp.at(0) = a;
  tmp.at(1) = b;
  tmp.at(2) = c;
  tmp.at(3) = d;
  
  _texcoords.buffersubdata (0, tmp.size() * sizeof(glm::vec4), &tmp.front());
}


///////////////////////////////////////////////////////////////////////////////
void      
plane::normal (glm::vec4 const& n)
{
  // normal in z-axis
  std::vector<glm::vec4> normals(4, n);
  _normals.buffersubdata (0, unsigned(  normals.size() * sizeof(glm::vec4)),   &normals.front());
}


///////////////////////////////////////////////////////////////////////////////
void      
plane::attrib_location (GLint vertexattrib_index, GLint normalattrib_index, GLint texcoordattrib_index)
{
  // bind vertices to generic attribute and enable array
  if (vertexattrib_index >= 0) 
  {  
    _vao.attrib_array(_vertices, vertexattrib_index, 4, GL_FLOAT, false, 0, 0);
    _vao.enable_attrib(vertexattrib_index);
  }

  // bind normals to generic attribute and enable array
  if (normalattrib_index >= 0) 
  {
    _vao.attrib_array(_normals, normalattrib_index, 4, GL_FLOAT, false, 0, 0);
    _vao.enable_attrib(normalattrib_index);
  }

  // bind texcoords to generic attribute and enable array
  if (texcoordattrib_index >= 0) 
  {
    _vao.attrib_array(_texcoords, texcoordattrib_index, 4, GL_FLOAT, false, 0, 0);
    _vao.enable_attrib(texcoordattrib_index);
  }
}


///////////////////////////////////////////////////////////////////////////////
void 
plane::draw()
{
  _vao.bind();
  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
  _vao.unbind();
}

} } // namespace unvox / namespace gl

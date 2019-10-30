//******************************************************************************
// Module: UnVox
// Author: Sebastian Thiele / Andre Schollmeyer
// 
// Copyright 2019 
// All rights reserved
//******************************************************************************
#include "gl/primitives/line.hpp"

#include <iostream>
#include <vector>
#include <cassert>

#include <glm/glm.hpp>

namespace unvox { namespace gl {

///////////////////////////////////////////////////////////////////////////////
line::line(std::vector<glm::vec4> const& points,
                 GLint vertexattrib_index,  
                 GLint normalattrib_index, 
                 GLint texcoordattrib_index )
  : _count     ( int(points.size()) ),
    _vao       (),
    _vertices  ( points.size() * sizeof(glm::vec4) ),
    _colors    ( points.size() * sizeof(glm::vec4) ),
    _texcoords ( points.size() * sizeof(glm::vec4) )
{  
  _vertices.buffersubdata (0, unsigned( points.size() * sizeof(glm::vec4)),  &points.front());
  attrib_location (vertexattrib_index, normalattrib_index, texcoordattrib_index);
}

///////////////////////////////////////////////////////////////////////////////
line::~line()
{}


///////////////////////////////////////////////////////////////////////////////
void      
line::set_color ( std::vector<glm::vec4> const& color )
{
  assert ( _count == color.size() ); 
  _colors.buffersubdata (0, unsigned( color.size() * sizeof(glm::vec4)),  &color.front());  
}


///////////////////////////////////////////////////////////////////////////////
void      
line::set_texcoords ( std::vector<glm::vec4> const& texcoords )
{
  assert ( _count == texcoords.size() ); 
  _colors.buffersubdata (0, unsigned( texcoords.size() * sizeof(glm::vec4)),  &texcoords.front());  
}


///////////////////////////////////////////////////////////////////////////////
void      
line::attrib_location (GLint vertexattrib_index, GLint colorattrib_index, GLint texcoordattrib_index)
{
  // bind vertices to generic attribute and enable array
  if (vertexattrib_index >= 0) 
  {  
    _vao.attrib_array(_vertices, vertexattrib_index, 4, GL_FLOAT, false, 0, 0);
    _vao.enable_attrib(vertexattrib_index);
  }

  // bind normals to generic attribute and enable array
  if (colorattrib_index >= 0) 
  {
    _vao.attrib_array(_colors, colorattrib_index, 4, GL_FLOAT, false, 0, 0);
    _vao.enable_attrib(colorattrib_index);
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
line::draw(float linewidth )
{
  glLineWidth(linewidth);
  _vao.bind();
  glDrawArrays(GL_LINE_STRIP, 0, _count);
  _vao.unbind();
}

} } // namespace unvox / namespace gl

//******************************************************************************
// Module: UnVox
// Author: Sebastian Thiele / Andre Schollmeyer
// 
// Copyright 2019 
// All rights reserved
//******************************************************************************
#ifndef UNVOX_GL_PLANE_HPP
#define UNVOX_GL_PLANE_HPP

#include <gl/glpp.hpp>

#include <gl/arraybuffer.hpp>
#include <gl/vertexarrayobject.hpp>
#include <glm/glm.hpp>


namespace unvox { namespace gl {

  class UNVOX_GL plane
{
public :

  plane                     ( GLint vertexattrib_index, GLint normalattrib_index, GLint texcoordattrib_index );
  ~plane                    ( );

  plane(plane const&  other) = delete;
  plane operator=(plane const&  other) = delete;

public :

  void      size            ( float width, float height );

  void      texcoords       ( glm::vec4 const& a, 
                              glm::vec4 const& b, 
                              glm::vec4 const& c, 
                              glm::vec4 const& d);

  void      normal          ( glm::vec4 const& n );

  void      attrib_location ( GLint vertexattrib_index, 
                              GLint normalattrib_index, 
                              GLint texcoordattrib_index );

  void      draw            ( );

private :

  arraybuffer         _vertices;
  arraybuffer         _normals;
  arraybuffer         _texcoords;

  vertexarrayobject   _vao;
};

} } // namespace unvox / namespace gl

#endif // UNVOX_GL_PLANE_HPP

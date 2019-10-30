//******************************************************************************
// Module: UnVox
// Author: Sebastian Thiele / Andre Schollmeyer
// 
// Copyright 2019 
// All rights reserved
//******************************************************************************
#ifndef UNVOX_GL_LINE_HPP
#define UNVOX_GL_LINE_HPP

#include <vector>
#include <gl/glpp.hpp>

#include <gl/arraybuffer.hpp>
#include <gl/vertexarrayobject.hpp>

#include <glm/glm.hpp>

namespace unvox { namespace gl {

  class UNVOX_GL line 
{
public :

  line                      ( std::vector<glm::vec4> const& points, 
                              GLint vertexattrib_index = 0, 
                              GLint colorattrib_index = 1, 
                              GLint texcoordattrib_index = 2 );
  ~line                     ( );

  line(line const& other) = delete;
  line& operator=(line const& other) = delete;

public :

  void      set_color       ( std::vector<glm::vec4> const& color );
  void      set_texcoords   ( std::vector<glm::vec4> const& texcoords );

  void      attrib_location ( GLint vertexattrib_index, 
                              GLint colorattrib_index, 
                              GLint texcoordattrib_index );

  void      draw            ( float linewidth = 1.0f );

private :

  unsigned            _count;

  arraybuffer         _vertices;
  arraybuffer         _colors;
  arraybuffer         _texcoords;

  vertexarrayobject   _vao;
};

} } // namespace unvox / namespace gl

#endif // UNVOX_GL_LINE_HPP

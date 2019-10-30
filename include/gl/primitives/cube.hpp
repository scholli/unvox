//******************************************************************************
// Module: UnVox
// Author: Sebastian Thiele / Andre Schollmeyer
// 
// Copyright 2019 
// All rights reserved
//******************************************************************************
#ifndef UNVOX_GL_CUBE_HPP
#define UNVOX_GL_CUBE_HPP

#include <vector>

#include <gl/glpp.hpp>

#include <gl/arraybuffer.hpp>
#include <gl/vertexarrayobject.hpp>
#include <gl/elementarraybuffer.hpp>
#include <glm/glm.hpp>


namespace unvox { namespace gl {

class UNVOX_GL cube
{
public : // c'tor/d'tor

  cube             ( GLint vertexattrib_index   = 0,
                     GLint colorattrib_index    = 1,
                     GLint normalattrib_index   = 2,
                     GLint texcoordattrib_index = 3 );

  ~cube            ( );

  cube(cube const&  other) = delete;
  cube operator=(cube const&  other) = delete;

public : // methods

  void draw            ( bool wireframe = false );

  void set_vertices    ( glm::vec4 const& lbf = glm::vec4(-1.0f, -1.0f, -1.0f, 1.0f),
                         glm::vec4 const& rbf = glm::vec4( 1.0f, -1.0f, -1.0f, 1.0f),
                         glm::vec4 const& ltf = glm::vec4(-1.0f,  1.0f, -1.0f, 1.0f),
                         glm::vec4 const& rtf = glm::vec4( 1.0f,  1.0f, -1.0f, 1.0f),
                         glm::vec4 const& lbr = glm::vec4(-1.0f, -1.0f,  1.0f, 1.0f),
                         glm::vec4 const& rbr = glm::vec4( 1.0f, -1.0f,  1.0f, 1.0f),
                         glm::vec4 const& ltr = glm::vec4(-1.0f,  1.0f,  1.0f, 1.0f),
                         glm::vec4 const& rtr = glm::vec4( 1.0f,  1.0f,  1.0f, 1.0f) ); // left/right(l/r) - bottom/top(b/t) - front/rear(f/r)

  void set_colors      ( glm::vec4 const& lbf = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
                         glm::vec4 const& rbf = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
                         glm::vec4 const& ltf = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
                         glm::vec4 const& rtf = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f),
                         glm::vec4 const& lbr = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
                         glm::vec4 const& rbr = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f),
                         glm::vec4 const& ltr = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f),
                         glm::vec4 const& rtr = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)); // left/right(l/r) - bottom/top(b/t) - front/rear(f/r)

  void set_texcoords   ( glm::vec4 const& lbf = glm::vec4( 0.0f,  0.0f,  0.0f, 1.0f),
                         glm::vec4 const& rbf = glm::vec4( 1.0f,  0.0f,  0.0f, 1.0f),
                         glm::vec4 const& ltf = glm::vec4( 0.0f,  1.0f,  0.0f, 1.0f),
                         glm::vec4 const& rtf = glm::vec4( 1.0f,  1.0f,  0.0f, 1.0f),
                         glm::vec4 const& lbr = glm::vec4( 0.0f,  0.0f,  1.0f, 1.0f),
                         glm::vec4 const& rbr = glm::vec4( 1.0f,  0.0f,  1.0f, 1.0f),
                         glm::vec4 const& ltr = glm::vec4( 0.0f,  1.0f,  1.0f, 1.0f),
                         glm::vec4 const& rtr = glm::vec4( 1.0f,  1.0f,  1.0f, 1.0f) ); // left/right(l/r) - bottom/top(b/t) - front/rear(f/r)

  static std::vector< glm::vec4> create_triangle_mesh (  glm::vec4 const& lbf,
                                                     glm::vec4 const& rbf,
                                                     glm::vec4 const& ltf,
                                                     glm::vec4 const& rtf,
                                                     glm::vec4 const& lbr,
                                                     glm::vec4 const& rbr,
                                                     glm::vec4 const& ltr,
                                                     glm::vec4 const& rtr );
  
  static void create_triangle_mesh ( glm::vec4 const& lbf,
                                     glm::vec4 const& rbf,
                                     glm::vec4 const& ltf,
                                     glm::vec4 const& rtf,
                                     glm::vec4 const& lbr,
                                     glm::vec4 const& rbr,
                                     glm::vec4 const& ltr,
                                     glm::vec4 const& rtr,
                                     std::vector< glm::vec4>& attributes,
                                     std::vector<int>&    mesh_indices,
                                     std::vector<int>&    line_indices );
    
  void      set_color       ( float r, float g, float b, float a = 1.0);

private : // methods

  void      _init           ( GLint vertexattrib_index,
                              GLint colorattrib_index,
                              GLint normalattrib_index,
                              GLint texcoordattrib_index );

  void      _init_color     ( float r = 1.0,
                              float g = 1.0,
                              float b = 1.0,
                              float a = 1.0);

  //void      _init_normals   ( );

private : // members

  arraybuffer         _vertices;
  arraybuffer         _colors;
  arraybuffer         _normals;
  arraybuffer         _texcoords;

  elementarraybuffer  _triangles;
  elementarraybuffer  _lines;

  vertexarrayobject   _vao;

};

} } // namespace unvox / namespace gl

#endif // UNVOX_GL_CUBE_HPP

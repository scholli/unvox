//******************************************************************************
// Module: UnVox
// Author: Sebastian Thiele / Andre Schollmeyer
// 
// Copyright 2019 
// All rights reserved
//******************************************************************************
#include "gl/primitives/cube.hpp"

#include <vector>

#include <glm/glm.hpp>
#include <gl/error.hpp>
#include <gl/elementarraybuffer.hpp>

namespace unvox { namespace gl {

///////////////////////////////////////////////////////////////////////////////
cube::cube(int vertexindex, int colorindex, int normalindex, int texcoordindex )
  : _vertices   (),
    _colors     (),
    _normals    (),
    _texcoords  (),
    _triangles  (),
    _lines      (),
    _vao        ()
{
  _init(vertexindex, colorindex, normalindex, texcoordindex);

  //       7______8
  //      /.     /|
  //     / .    / |
  //    3------4  |           +y   +z
  //    |  5. .| ./6           |  /
  //    | .    | /             | /
  //    --------/              ----- +x
  //    1      2

  unsigned mesh_indices[36];
  for (unsigned index = 0; index != 36; ++index) {
    mesh_indices[index] = index;
  }
  _triangles.bufferdata(sizeof(mesh_indices), (void*)mesh_indices, GL_STATIC_DRAW);

  unsigned line_indices[36] = { 0, 2, 1, 2, 3, 4, 4, 5, 
                                6, 8, 7, 8, 9, 10, 10, 11, 
                                12, 14, 16, 17, 20, 21, 22, 23};
  _lines.bufferdata(sizeof(line_indices), (void*)line_indices, GL_STATIC_DRAW);
}


///////////////////////////////////////////////////////////////////////////////
cube::~cube()
{}


///////////////////////////////////////////////////////////////////////////////
void
cube::draw(bool wireframe)
{
  _vao.bind();

  if (wireframe)
  {
    _lines.bind();
    glDrawElementsBaseVertex(GL_LINES, 24, GL_UNSIGNED_INT, 0, 0);
  } else {
    _triangles.bind();
    glDrawElementsBaseVertex(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, 0);
  }

  _vao.unbind();
}


///////////////////////////////////////////////////////////////////////////////
void    
cube::set_vertices (glm::vec4 const& lbf,// 1
                    glm::vec4 const& rbf,// 2 
                    glm::vec4 const& ltf,// 3
                    glm::vec4 const& rtf,// 4
                    glm::vec4 const& lbr,// 5
                    glm::vec4 const& rbr,// 6
                    glm::vec4 const& ltr,// 7
                    glm::vec4 const& rtr // 8
                   )
{
  std::vector<glm::vec4> vertices = create_triangle_mesh ( lbf, rbf, ltf, rtf, lbr, rbr, ltr, rtr );

  // upload vertices 
  _vertices.buffersubdata ( 0, unsigned( vertices.size() * sizeof(glm::vec4)),  &vertices.front());

  // compute normals
  std::vector<glm::vec3> normals(36);

  //       6______5
  //      /.     /|
  //     / .    / |
  //    2------1  |           +y   +z
  //    |  7. .| ./8           |  /
  //    | .    | /             | /
  //    --------/              ----- +x
  //    4      3

  glm::vec3 top    = cross( glm::vec3(ltr-ltf), glm::vec3(rtr-ltf) );
  glm::vec3 bottom = cross( glm::vec3(rbr-lbf), glm::vec3(lbr-lbf) );
  glm::vec3 front  = cross( glm::vec3(ltf-lbf), glm::vec3(rbf-lbf) );
  glm::vec3 back   = cross( glm::vec3(rbr-lbr), glm::vec3(ltr-lbr) );
  glm::vec3 left   = cross( glm::vec3(lbr-lbf), glm::vec3(ltr-lbf) ); 
  glm::vec3 right  = cross( glm::vec3(rtf-rbf), glm::vec3(rbr-rbf) ); 

  // use flat shading to get correct per-surface normal
  std::fill_n(normals.begin()     , 6, top   );
  std::fill_n(normals.begin() + 6 , 6, bottom);
  std::fill_n(normals.begin() + 12, 6, front );
  std::fill_n(normals.begin() + 18, 6, back  );
  std::fill_n(normals.begin() + 24, 6, left  );
  std::fill_n(normals.begin() + 30, 6, right );

  _normals.buffersubdata  ( 0, unsigned(  normals.size() * sizeof(glm::vec3)),   &normals.front());
}


///////////////////////////////////////////////////////////////////////////////
void
cube::set_color ( float r, float g, float b, float a)
{
  _init_color(r, g, b, a);
}


///////////////////////////////////////////////////////////////////////////////
void
cube::_init ( GLint vertexattrib_index,
              GLint colorattrib_index,
              GLint normalattrib_index,
              GLint texcoordattrib_index)
{
  // allocate memory
  _vertices.bufferdata  (36 * sizeof(glm::vec4), 0);
  _normals.bufferdata   (36 * sizeof(glm::vec3), 0);
  _colors.bufferdata    (36 * sizeof(glm::vec4), 0);
  _texcoords.bufferdata (36 * sizeof(glm::vec4), 0);

  // set data for cube
  set_vertices();
  set_texcoords();
  _init_color();

  if (vertexattrib_index >=0) {
    // bind vertices to generic attribute and enable array
    _vao.attrib_array(_vertices, vertexattrib_index, 4, GL_FLOAT, false, 0, 0);
    _vao.enable_attrib(vertexattrib_index);
  }

  if (colorattrib_index >=0) {
    // bind vertices to generic attribute and enable array
    _vao.attrib_array(_colors, colorattrib_index, 4, GL_FLOAT, false, 0, 0);
    _vao.enable_attrib(colorattrib_index);
  }

  if (normalattrib_index >=0) {
    // bind vertices to generic attribute and enable array
    _vao.attrib_array(_normals, normalattrib_index, 3, GL_FLOAT, false, 0, 0);
    _vao.enable_attrib(normalattrib_index);
  }

  if (texcoordattrib_index >=0) {
    // bind vertices to generic attribute and enable array
    _vao.attrib_array(_texcoords, texcoordattrib_index, 4, GL_FLOAT, false, 0, 0);
    _vao.enable_attrib(texcoordattrib_index);
  }
}


///////////////////////////////////////////////////////////////////////////////
void
cube::set_colors(glm::vec4 const& lbf,
                 glm::vec4 const& rbf,
                 glm::vec4 const& ltf,
                 glm::vec4 const& rtf,
                 glm::vec4 const& lbr,
                 glm::vec4 const& rbr,
                 glm::vec4 const& ltr,
                 glm::vec4 const& rtr)

{
  std::vector<glm::vec4> colors = create_triangle_mesh(lbf, rbf, ltf, rtf, lbr, rbr, ltr, rtr);
  _colors.buffersubdata(0, unsigned(colors.size() * sizeof(glm::vec4)), &colors.front());
}


///////////////////////////////////////////////////////////////////////////////
void
cube::set_texcoords (glm::vec4 const& lbf,
                     glm::vec4 const& rbf,
                     glm::vec4 const& ltf,
                     glm::vec4 const& rtf,
                     glm::vec4 const& lbr,
                     glm::vec4 const& rbr,
                     glm::vec4 const& ltr,
                     glm::vec4 const& rtr )

{
  std::vector<glm::vec4> texcoords = create_triangle_mesh ( lbf, rbf, ltf, rtf, lbr, rbr, ltr, rtr );
  _texcoords.buffersubdata( 0, unsigned(texcoords.size() * sizeof(glm::vec4)), &texcoords.front());
}


///////////////////////////////////////////////////////////////////////////////
std::vector<glm::vec4>
cube::create_triangle_mesh ( glm::vec4 const& lbf,
                             glm::vec4 const& rbf,
                             glm::vec4 const& ltf,
                             glm::vec4 const& rtf,
                             glm::vec4 const& lbr,
                             glm::vec4 const& rbr,
                             glm::vec4 const& ltr,
                             glm::vec4 const& rtr )
{
  std::vector<glm::vec4> attrib_array;

  //       7______8
  //      /.     /|
  //     / .    / |
  //    3------4  |           +y   +z
  //    |  5. .| ./6           |  /
  //    | .    | /             | /
  //    --------/              ----- +x
  //    1      2

  // top
  attrib_array.push_back(ltf); // 3
  attrib_array.push_back(rtr); // 8
  attrib_array.push_back(ltr); // 7 
  attrib_array.push_back(ltf); // 3 
  attrib_array.push_back(rtf); // 4 
  attrib_array.push_back(rtr); // 8 
      
  // bottom                 
  attrib_array.push_back(lbr); // 5 
  attrib_array.push_back(rbf); // 2 
  attrib_array.push_back(lbf); // 1 
  attrib_array.push_back(lbr); // 5 
  attrib_array.push_back(rbr); // 6 
  attrib_array.push_back(rbf); // 2 
                   
  // front                  
  attrib_array.push_back(lbf); // 1 
  attrib_array.push_back(rtf); // 4 
  attrib_array.push_back(ltf); // 3 
  attrib_array.push_back(lbf); // 1 
  attrib_array.push_back(rbf); // 2 
  attrib_array.push_back(rtf); // 4 
  
  // back                   
  attrib_array.push_back(rbr); // 6 
  attrib_array.push_back(ltr); // 7 
  attrib_array.push_back(rtr); // 8 
  attrib_array.push_back(rbr); // 6 
  attrib_array.push_back(lbr); // 5 
  attrib_array.push_back(ltr); // 7 
                            
  // left                   
  attrib_array.push_back(lbr); // 5 
  attrib_array.push_back(ltf); // 3 
  attrib_array.push_back(ltr); // 7 
  attrib_array.push_back(lbr); // 5 
  attrib_array.push_back(lbf); // 1 
  attrib_array.push_back(ltf); // 3 
               
  // right                  
  attrib_array.push_back(rbf); // 2 
  attrib_array.push_back(rtr); // 8 
  attrib_array.push_back(rtf); // 4 
  attrib_array.push_back(rbf); // 2 
  attrib_array.push_back(rbr); // 6 
  attrib_array.push_back(rtr); // 8 

  return attrib_array;
}


///////////////////////////////////////////////////////////////////////////////
void
cube::_init_color(float r, float g, float b, float a)
{
  std::vector<glm::vec4> colors(36);

  std::fill(colors.begin(), colors.end(), glm::vec4(r, g, b, a));

  _colors.buffersubdata( 0, unsigned( colors.size() * sizeof(glm::vec4)), &colors.front());
}


} } // namespace unvox / namespace gl

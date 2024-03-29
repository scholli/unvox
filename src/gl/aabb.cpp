//******************************************************************************
// Module: UnVox
// Author: Sebastian Thiele / Andre Schollmeyer
// 
// Copyright 2019 
// All rights reserved
//******************************************************************************

// header i/f
#include "gl/primitives/aabb.hpp"

// header, system
#include <gpucast/math/vec3.hpp>

#include <gl/program.hpp>
#include <gl/arraybuffer.hpp>
#include <gl/vertexarrayobject.hpp>


namespace gpucast {
  namespace gl {

////////////////////////////////////////////////////////////////////////////////
aabb::aabb ()
: base_type     (),
  _initialized  (false),
  _vertexarray  (),
  _colorarray   (),
  _arrayobject  (), 
  _program      (),
  _color        (0.5f, 0.5f, 0.5f, 1.0f)
{}


////////////////////////////////////////////////////////////////////////////////
aabb::aabb ( base_type const& b )
: base_type     (b),
  _initialized  (false),
  _vertexarray  (),
  _colorarray   (),
  _arrayobject  (),
  _program      (),
  _color        (0.5f, 0.5f, 0.5f, 1.0f)
{}


////////////////////////////////////////////////////////////////////////////////
aabb::~aabb ()
{}


////////////////////////////////////////////////////////////////////////////////
void 
aabb::draw ( gpucast::math::matrix4x4<float> const& mvp  )
{
  _init ();

  _program->begin();
  {
    _program->set_uniform_matrix4fv( "mvp", 1, 0, &mvp[0]);
    _arrayobject->bind();
    {
      glDrawArrays ( GL_LINES, 0, 24 );
    }
    _arrayobject->unbind();
  }
  _program->end ();
}


////////////////////////////////////////////////////////////////////////////////
void                      
aabb::color ( gpucast::math::vec4f const& color )
{
  if ( color != _color ) 
  {
    _color = color;

    // if already uploaded to GPU -> update color buffer
    if ( _initialized ) 
    {
      std::vector<gpucast::math::vec4f> colors (8);
      std::fill ( colors.begin(), colors.end(), gpucast::math::vec4f(_color) ); 
      _colorarray->update ( colors.begin(), colors.end() );
    }
  }
}


////////////////////////////////////////////////////////////////////////////////
void aabb::_init ( )
{
  // if already initialized -> initialize
  if (_initialized) return;

  // allocate ressources
  _vertexarray.reset  ( new gpucast::gl::arraybuffer );
  _colorarray.reset   ( new gpucast::gl::arraybuffer );
  _arrayobject.reset  ( new gpucast::gl::vertexarrayobject );
  _program.reset      ( new gpucast::gl::program );

  // compile shader and link program
  std::string const vs_src = R"(
    "#version 430 core 
     #extension GL_EXT_gpu_shader4 : enable 
      \n\
      layout (location = 0) in vec4 vertex; \n\
      layout (location = 1) in vec4 color;  \n\
      
      uniform mat4 mvp; 
      
      void main(void) 
      { 
        gl_Position   = mvp * vertex; 
        gl_FrontColor = color; 
      } 
      )";

  gpucast::gl::shader vs(gpucast::gl::vertex_stage);

  vs.set_source(vs_src.c_str());
  vs.compile();
  
  _program->add  (&vs);
  _program->link ();

  // generate data and copy to GPU
  std::vector<gpucast::math::vec3f> corners;
  generate_corners ( std::back_inserter( corners ) );

  std::vector<gpucast::math::vec3f> vertices;

  // points whose index differ one bit form one edge
  for (unsigned i = 0; i != corners.size(); ++i)
  {
    if ( i & 0x01 ) {
      unsigned k = i ^ 0x01;
      vertices.push_back(corners[i]);
      vertices.push_back(corners[k]);
    }

    if ( i & 0x02 ) {
      unsigned k = i ^ 0x02;
      vertices.push_back(corners[i]);
      vertices.push_back(corners[k]);
    }

    if ( i & 0x04 ) {
      unsigned k = i ^ 0x04;
      vertices.push_back(corners[i]);
      vertices.push_back(corners[k]);
    }
  }

  std::vector<gpucast::math::vec4f> colors ( vertices.size() );
  std::fill(colors.begin(), colors.end(), _color);

  _vertexarray->update ( vertices.begin(),  vertices.end() );
  _colorarray->update  ( colors.begin(),    colors.end()   );

  _arrayobject->bind();

  _arrayobject->attrib_array  ( *_vertexarray, 0, 3, GL_FLOAT, false, 0, 0 );
  _arrayobject->enable_attrib ( 0 );
  _arrayobject->attrib_array  ( *_colorarray, 1, 4, GL_FLOAT, false, 0, 0 );
  _arrayobject->enable_attrib ( 1 );

  _arrayobject->unbind();

  _initialized = true;
}


  } // namespace gl
} // namespace gpucast 


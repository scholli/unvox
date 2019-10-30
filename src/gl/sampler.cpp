//******************************************************************************
// Module: UnVox
// Author: Sebastian Thiele / Andre Schollmeyer
// 
// Copyright 2019 
// All rights reserved
//******************************************************************************
#include "gl/sampler.hpp"

// header system
#include <vector>
#include <iostream>
#include <exception>

// header dependencies
#include <GL/glew.h>

// header project


namespace unvox { namespace gl {

///////////////////////////////////////////////////////////////////////////////
sampler::sampler()
: _id       ( 0 )
{
  glGenSamplers ( 1, &_id );

  // set default
  parameter ( GL_TEXTURE_MIN_FILTER, GL_LINEAR );
  parameter ( GL_TEXTURE_MAG_FILTER, GL_LINEAR );

  parameter ( GL_TEXTURE_WRAP_R, GL_REPEAT );
  parameter ( GL_TEXTURE_WRAP_S, GL_REPEAT );
  parameter ( GL_TEXTURE_WRAP_T, GL_REPEAT );
}


///////////////////////////////////////////////////////////////////////////////
sampler::~sampler( )
{
  glDeleteSamplers ( 1, &_id );
}


///////////////////////////////////////////////////////////////////////////////
void            
sampler::swap( sampler& other)
{
  std::swap ( _id, other._id );
}


///////////////////////////////////////////////////////////////////////////////
void          
sampler::parameter ( GLenum pname,
                     GLint  param ) const
{
  glSamplerParameteri ( _id, pname, param );
}


///////////////////////////////////////////////////////////////////////////////
void          
sampler::parameter ( GLenum  pname,
                     GLfloat param ) const
{
  glSamplerParameterf ( _id, pname, param );
}


///////////////////////////////////////////////////////////////////////////////
void            
sampler::bind ( GLint unit ) const
{
  glBindSampler ( unit, _id );
}


///////////////////////////////////////////////////////////////////////////////
void            
sampler::unbind () const
{
  glBindSampler ( 0, _id );
}


} } // namespace unvox / namespace gl

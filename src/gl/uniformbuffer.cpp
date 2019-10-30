//******************************************************************************
// Module: UnVox
// Author: Sebastian Thiele / Andre Schollmeyer
// 
// Copyright 2019 
// All rights reserved
//******************************************************************************
#include "gl/uniformbuffer.hpp"

// header system
#include <vector>
#include <iostream>
#include <cstring>
#include <exception>

// header dependencies

// header project
#include <glm/glm.hpp>
//#include <gl/state.hpp>


namespace unvox { namespace gl {

///////////////////////////////////////////////////////////////////////////////
uniformbuffer::uniformbuffer()
: buffer()
{}


///////////////////////////////////////////////////////////////////////////////
uniformbuffer::uniformbuffer                  ( std::size_t bytes, GLenum usage )
: buffer   ( bytes, usage )
{}


///////////////////////////////////////////////////////////////////////////////
uniformbuffer::~uniformbuffer                 ( )
{}


///////////////////////////////////////////////////////////////////////////////
void            
uniformbuffer::swap( uniformbuffer& t)
{
  buffer::swap(t);
}


///////////////////////////////////////////////////////////////////////////////
void            
uniformbuffer::bind() const
{
  glBindBuffer (target(), id());
}


///////////////////////////////////////////////////////////////////////////////
void            
uniformbuffer::bindbase(GLuint base) const
{
  glBindBufferBase (target(), base, id());
}


///////////////////////////////////////////////////////////////////////////////
void            
uniformbuffer::unbind() const
{
  glBindBuffer (target(), 0);
}


///////////////////////////////////////////////////////////////////////////////
GLenum 
uniformbuffer::target() const
{
  return GL_UNIFORM_BUFFER;
}


} } // namespace unvox / namespace gl

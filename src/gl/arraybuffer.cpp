//******************************************************************************
// Module: UnVox
// Author: Sebastian Thiele / Andre Schollmeyer
// 
// Copyright 2019 
// All rights reserved
//******************************************************************************
#include "gl/arraybuffer.hpp"

// header system
#include <vector>
#include <iostream>
#include <exception>

// header dependencies
#include <GL/glew.h>

namespace unvox { namespace gl {

///////////////////////////////////////////////////////////////////////////////
arraybuffer::arraybuffer()
: buffer  ()
{}


///////////////////////////////////////////////////////////////////////////////
arraybuffer::arraybuffer( std::size_t bytes, GLenum usage )
: buffer ( bytes, usage )
{}


///////////////////////////////////////////////////////////////////////////////
arraybuffer::~arraybuffer( )
{
  unbind();
}


///////////////////////////////////////////////////////////////////////////////
void            
arraybuffer::swap( arraybuffer& t)
{
  buffer::swap(t);
}


///////////////////////////////////////////////////////////////////////////////
void            
arraybuffer::bind() const
{
  glBindBuffer (target(), id());
}


///////////////////////////////////////////////////////////////////////////////
void            
arraybuffer::unbind() const
{
  glBindBuffer (target(), 0);
}


///////////////////////////////////////////////////////////////////////////////
GLenum          
arraybuffer::target( ) const
{
  return GL_ARRAY_BUFFER;
}
 
} } // namespace unvox / namespace gl

//******************************************************************************
// Module: UnVox
// Author: Sebastian Thiele / Andre Schollmeyer
// 
// Copyright 2019 
// All rights reserved
//******************************************************************************
#include "gl/elementarraybuffer.hpp"

// header system
#include <vector>
#include <iostream>
#include <exception>

// header dependencies
#include <GL/glew.h>

namespace unvox { namespace gl {

///////////////////////////////////////////////////////////////////////////////
elementarraybuffer::elementarraybuffer()
: buffer( )
{}


///////////////////////////////////////////////////////////////////////////////
elementarraybuffer::elementarraybuffer( std::size_t bytes, GLenum usage )
: buffer( bytes, usage )
{}


///////////////////////////////////////////////////////////////////////////////
elementarraybuffer::~elementarraybuffer()
{
  unbind();
}


///////////////////////////////////////////////////////////////////////////////
void            
elementarraybuffer::swap( elementarraybuffer& t)
{
  buffer::swap(t);
}


///////////////////////////////////////////////////////////////////////////////
void            
elementarraybuffer::bind() const
{
  glBindBuffer (target(), id());
}


///////////////////////////////////////////////////////////////////////////////
void            
elementarraybuffer::unbind() const
{
  glBindBuffer (target(), 0);
}


///////////////////////////////////////////////////////////////////////////////
/* static */ GLenum   
elementarraybuffer::target( ) const
{
  return GL_ELEMENT_ARRAY_BUFFER;
}
 

} } // namespace unvox / namespace gl

//******************************************************************************
// Module: UnVox
// Author: Sebastian Thiele / Andre Schollmeyer
// 
// Copyright 2019 
// All rights reserved
//******************************************************************************
#include "gl/shaderstoragebuffer.hpp"

// header system
#include <vector>
#include <iostream>
#include <exception>

// header dependencies
#include <GL/glew.h>

// header project
#include <glm/glm.hpp>

namespace unvox { namespace gl {

///////////////////////////////////////////////////////////////////////////////
  shaderstoragebuffer::shaderstoragebuffer()
: buffer  ()
{}


///////////////////////////////////////////////////////////////////////////////
  shaderstoragebuffer::shaderstoragebuffer(std::size_t bytes, GLenum usage)
: buffer ( bytes, usage )
{}


///////////////////////////////////////////////////////////////////////////////
  shaderstoragebuffer::~shaderstoragebuffer()
{
  unbind();
}


///////////////////////////////////////////////////////////////////////////////
void            
shaderstoragebuffer::swap(shaderstoragebuffer& t)
{
  buffer::swap(t);
}


///////////////////////////////////////////////////////////////////////////////
void            
shaderstoragebuffer::bind() const
{
  glBindBuffer (target(), id());
}

///////////////////////////////////////////////////////////////////////////////
void            
shaderstoragebuffer::unbind() const
{
  glBindBuffer (target(), 0);
}


///////////////////////////////////////////////////////////////////////////////
GLenum          
shaderstoragebuffer::target() const
{
  return GL_SHADER_STORAGE_BUFFER;
}
 
} } // namespace unvox / namespace gl

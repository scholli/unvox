//******************************************************************************
// Module: UnVox
// Author: Sebastian Thiele / Andre Schollmeyer
// 
// Copyright 2019 
// All rights reserved
//******************************************************************************
#include "gl/vertexarrayobject.hpp"

// header system
#include <iostream>

// header dependencies

// header project
#include <gl/buffer.hpp>
#include <gl/error.hpp>

namespace unvox { namespace gl {

///////////////////////////////////////////////////////////////////////////////
vertexarrayobject::vertexarrayobject()
: _id     ()
{ 
  glGenVertexArrays (1, &_id);
}

///////////////////////////////////////////////////////////////////////////////
vertexarrayobject::~vertexarrayobject()
{
  glDeleteVertexArrays (1, &_id);
}


///////////////////////////////////////////////////////////////////////////////
void            
vertexarrayobject::bind() const
{
  glBindVertexArray(_id);
}


///////////////////////////////////////////////////////////////////////////////
void            
vertexarrayobject::unbind() const
{
  glBindVertexArray (0);
}


///////////////////////////////////////////////////////////////////////////////
void
vertexarrayobject::enable_attrib (std::size_t index) const
{
#if UNVOX_GL_DIRECT_STATE_ACCESS
  glEnableVertexArrayAttribEXT(_id, GLuint(index));
#else  
  bind();
  glEnableVertexAttribArray( GLuint(index) );
  unbind();
#endif
}


///////////////////////////////////////////////////////////////////////////////
void
vertexarrayobject::disable_attrib (std::size_t index) const
{
#if UNVOX_GL_DIRECT_STATE_ACCESS
  glDisableVertexArrayAttribEXT(_id, GLuint(index));
#else  
  bind();
  glDisableVertexAttribArray( GLuint(index) );
  unbind();
#endif
}


///////////////////////////////////////////////////////////////////////////////
void 
vertexarrayobject::attrib_array ( buffer const& buf, std::size_t index, std::size_t size, GLenum type, bool normalized, std::size_t stride, std::size_t offset ) const
{
#if UNVOX_GL_DIRECT_STATE_ACCESS
  // workaround
  buf.bind();
  switch ( type ) 
  {
    case GL_FLOAT         : glVertexArrayVertexAttribOffsetEXT (GLuint(_id), GLuint(buf.id()), GLuint(index), GLint(size), type, normalized, GLint(stride), GLintptr(offset)); break;
    case GL_BYTE          : glVertexArrayVertexAttribOffsetEXT (GLuint(_id), GLuint(buf.id()), GLuint(index), GLint(size), type, normalized, GLint(stride), GLintptr(offset)); break;
    case GL_UNSIGNED_INT  : glVertexArrayVertexAttribIOffsetEXT(GLuint(_id), GLuint(buf.id()), GLuint(index), GLint(size), type, GLint(stride), GLintptr(offset)); break;
    default : std::cerr << "vertexarrayobject::attrib_array() : type not handled yet" << std::endl;
  }
  buf.unbind();
#else 
  bind();
  buf.bind();
  switch ( type ) 
  {
    case GL_FLOAT         : glVertexAttribPointer(index, size, type, normalized, stride, pointer); break;
    case GL_UNSIGNED_INT  : glVertexAttribIPointer(index, size, type, stride, pointer); break;
    default : std::cerr << "vertexarrayobject::attrib_array() : type not handled yet" << std::endl;
  }
  buf.unbind();
  unbind();
#endif
}


} } // namespace unvox / namespace gl

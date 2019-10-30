//******************************************************************************
// Module: UnVox
// Author: Sebastian Thiele / Andre Schollmeyer
// 
// Copyright 2019 
// All rights reserved
//******************************************************************************
#include "gl/texturebuffer.hpp"

// header system
#include <vector>
#include <iostream>
#include <exception>

// header dependencies

// header project
#include <glm/glm.hpp>
#include <gl/error.hpp>


namespace unvox { namespace gl {

///////////////////////////////////////////////////////////////////////////////
texturebuffer::texturebuffer()
: buffer  ( ),
  _texid  ( 0 ),
  _unit   ( -1 ),
  _format ( GL_RGBA32F )
{
  glGenTextures(1, &_texid);
}


///////////////////////////////////////////////////////////////////////////////
texturebuffer::texturebuffer(std::size_t  size,
                             GLenum       usage,
                             GLenum       texformat)
: buffer  ( size, usage),
  _texid  ( 0 ),
  _unit   ( -1 ),
  _format ( texformat )
{
  glGenTextures(1, &_texid);
}


///////////////////////////////////////////////////////////////////////////////
texturebuffer::~texturebuffer()
{
  unbind();
  glDeleteTextures(1, &_texid);
}


///////////////////////////////////////////////////////////////////////////////
void            
texturebuffer::swap( texturebuffer& other)
{
  buffer::swap( other );
  std::swap   ( _texid,  other._texid );
  std::swap   ( _unit,   other._unit );
  std::swap   ( _format, other._format );
}


///////////////////////////////////////////////////////////////////////////////
void 
texturebuffer::format( GLenum f )
{
  _format = f;
#if UNVOX_GL_DIRECT_STATE_ACCESS
  glTextureBufferEXT(_texid, target(), _format, id());
#else
  glBindTexture (target(), _texid);
  glTexBufferARB(target(), _format, id());
  glBindTexture (target(), 0);
#endif
}


///////////////////////////////////////////////////////////////////////////////
/* virtual */ void  
texturebuffer::bind ( ) const
{
#if UNVOX_GL_DIRECT_STATE_ACCESS
  glBindMultiTextureEXT (GL_TEXTURE0, target(), _texid);
#else 
  glBindTexture (target(), _texid);
#endif
}


///////////////////////////////////////////////////////////////////////////////
void            
texturebuffer::bind(GLint texunit)
{
  if ( _unit >= 0 ) {
    unbind();
  }
  _unit = texunit;

#if UNVOX_GL_DIRECT_STATE_ACCESS
  glBindMultiTextureEXT(GL_TEXTURE0 + _unit, target(), _texid);
#else 
  glActiveTexture (GL_TEXTURE0 + _unit);
  glBindTexture   (target(), _texid);
#endif
}


///////////////////////////////////////////////////////////////////////////////
void                
texturebuffer::bind_as_image ( GLuint imageunit, GLint level, GLboolean layered, GLint layer, GLenum access, GLint format )
{
  glBindImageTextureEXT(imageunit, _texid, level, layered, layer, access, format);
}


///////////////////////////////////////////////////////////////////////////////
void            
texturebuffer::unbind()
{
  if (_unit >= 0) 
  {
#if UNVOX_GL_DIRECT_STATE_ACCESS
    glBindMultiTextureEXT (GL_TEXTURE0 + _unit, target(), 0);
#else 
    glActiveTexture (GL_TEXTURE0 + _unit);
    glBindTexture   (target(), 0);
#endif
    _unit = -1;
  }
}


///////////////////////////////////////////////////////////////////////////////
void            
texturebuffer::unbind() const
{
  if (_unit >= 0) 
  {
#if UNVOX_GL_DIRECT_STATE_ACCESS
    glBindMultiTextureEXT (GL_TEXTURE0 + _unit, target(), 0);
#else 
    glActiveTexture (GL_TEXTURE0 + _unit);
    glBindTexture   (target(), 0);
#endif
  }
}


///////////////////////////////////////////////////////////////////////////////
GLuint       
texturebuffer::texid( ) const
{
  return _texid;
}


///////////////////////////////////////////////////////////////////////////////
GLenum   
texturebuffer::target() const
{
  return GL_TEXTURE_BUFFER_EXT;
}

} } // namespace unvox / namespace gl

//******************************************************************************
// Module: UnVox
// Author: Sebastian Thiele / Andre Schollmeyer
// 
// Copyright 2019 
// All rights reserved
//******************************************************************************
#include "gl/buffer.hpp"

// header system
#include <vector>
#include <iostream>
#include <exception>
#include <cassert>

// header dependencies
#include <GL/glew.h>

// header project
#include <gl/error.hpp>

namespace unvox { namespace gl {

///////////////////////////////////////////////////////////////////////////////
buffer::buffer(GLenum usage)
: _id       ( 0 ),
  _usage    ( usage ),
  _capacity ( 0 )
{
  glGenBuffers (1, &_id);
}


///////////////////////////////////////////////////////////////////////////////
buffer::buffer( std::size_t bytes, GLenum usage )
: _id       ( 0 ),
  _usage    ( usage ),
  _capacity ( bytes )
{
  glGenBuffers( 1, &_id );
  bufferdata  ( bytes, 0 );
}


///////////////////////////////////////////////////////////////////////////////
buffer::~buffer()
{
  glDeleteBuffers(1, &_id);
}


///////////////////////////////////////////////////////////////////////////////
void            
buffer::swap( buffer& t)
{
  std::swap ( _id,        t._id );
  std::swap ( _usage,     t._usage );
  std::swap ( _capacity,  t._capacity );
}


///////////////////////////////////////////////////////////////////////////////
void 
buffer::bufferdata( std::size_t   bytes,
                    GLvoid const* data,
                    GLenum        usage )
{
  _usage = usage;

#if UNVOX_GL_DIRECT_STATE_ACCESS
  glNamedBufferDataEXT(_id, bytes, data, _usage);
#else
  glBindBuffer (target(), _id);
  glBufferData (target(), GLuint(bytes), data, _usage);
#endif
  _capacity = bytes;
}


///////////////////////////////////////////////////////////////////////////////
void 
buffer::buffersubdata( std::size_t    offset_bytes,
                       std::size_t    bytes,
                       GLvoid const*  data ) const
{
  assert(offset_bytes + bytes <= _capacity);
#if UNVOX_GL_DIRECT_STATE_ACCESS
  glNamedBufferSubDataEXT(_id, offset_bytes, bytes, data);
#else
  glBindBuffer   (target(), _id);
  glBufferSubData(target(), GLintptrARB(offset_bytes), GLintptrARB(bytes), data);
#endif
}


///////////////////////////////////////////////////////////////////////////////
void            
buffer::getbuffersubdata ( GLintptr     offset,
                           GLsizeiptr   size,
                           GLvoid*      data ) const
{
#if UNVOX_GL_DIRECT_STATE_ACCESS
  glGetNamedBufferSubDataEXT(_id, offset, size, data);
#else
  throw std::runtime_error("buffer::getbuffersubdata() only implemented with DSA.");
#endif
}


///////////////////////////////////////////////////////////////////////////////
GLuint64EXT            
buffer::address () const
{
  GLuint64EXT device_address;
  glGetBufferParameterui64vNV(target(), GL_BUFFER_GPU_ADDRESS_NV, &device_address); 
  return device_address;
}


///////////////////////////////////////////////////////////////////////////////
GLuint          
buffer::id( ) const
{
  return _id;
}

///////////////////////////////////////////////////////////////////////////////
GLenum          
buffer::usage ( ) const
{
  return _usage;
}

///////////////////////////////////////////////////////////////////////////////
std::size_t
buffer::capacity ( ) const
{
  return _capacity;
}


///////////////////////////////////////////////////////////////////////////////
GLint           
buffer::parameter ( GLenum parameter ) const
{
 #if UNVOX_GL_DIRECT_STATE_ACCESS
  GLint value;
  glGetNamedBufferParameterivEXT( _id, parameter, &value);
  return value;
#else
  throw std::runtime_error("buffer::parameter() only implemented with DSA.");
#endif
}


///////////////////////////////////////////////////////////////////////////////
void*           
buffer::map ( GLenum access ) const
{
#if UNVOX_GL_DIRECT_STATE_ACCESS
  return glMapNamedBufferEXT(_id, access);
#else
  throw std::runtime_error("buffer::map() only implemented with DSA.");
#endif
}


///////////////////////////////////////////////////////////////////////////////
void*           
buffer::map_range ( GLintptr offset, GLsizeiptr  length, GLbitfield  access ) const
{
#if UNVOX_GL_DIRECT_STATE_ACCESS
  return glMapNamedBufferRangeEXT(_id, offset, length, access);
#else
  throw std::runtime_error("buffer::map_range() only implemented with DSA.");
#endif
}


///////////////////////////////////////////////////////////////////////////////
bool buffer::unmap ( ) const
{
#if UNVOX_GL_DIRECT_STATE_ACCESS
  return glUnmapNamedBufferEXT(_id) ? true : false;
#else
  throw std::runtime_error("buffer::unmap() only implemented with DSA.");
#endif
}

 
///////////////////////////////////////////////////////////////////////////////
void            
buffer::make_resident ( ) const
{
  glMakeBufferResidentNV(target(), GL_READ_ONLY);
}
///////////////////////////////////////////////////////////////////////////////
void buffer::bind_range(unsigned in_index, std::size_t in_offset, std::size_t in_size)
{
  if ((0 > in_offset)
    || (0 > in_size)
    || (_capacity < (in_offset + in_size))) {
    std::runtime_error("buffer::bind_range(): Invalid range.\n");
  }

  if (0 < in_size) {
    glBindBufferRange(target(), in_index, id(), in_offset, in_size);
  }
}

///////////////////////////////////////////////////////////////////////////////
void buffer::unbind(unsigned binding_point)
{
  glBindBufferBase(target(), binding_point, 0);
}

///////////////////////////////////////////////////////////////////////////////
void buffer::bind_base(unsigned binding_point) const
{
  glBindBufferBase(target(), binding_point, id());
}

///////////////////////////////////////////////////////////////////////////////
void buffer::clear_data(GLenum internal_format, GLenum format, GLenum type, void* data)
{
#if 0 
  glClearNamedBufferDataEXT(id(), internal_format, format, type, data);
#else
  bind();
  glClearBufferData(target(), internal_format, format, type, data);
  unbind();
#endif
}

///////////////////////////////////////////////////////////////////////////////
void buffer::clear_subdata(GLenum internal_format, unsigned offset, unsigned size, GLenum format, GLenum type, void* data)
{
#if 0
  glClearNamedBufferSubDataEXT(id(), internal_format, offset, size, format, type, data);
#else 
  bind();
  glClearBufferSubData(target(), internal_format, offset, size, format, type, data);
  unbind();
#endif
}

} } // namespace unvox / namespace gl

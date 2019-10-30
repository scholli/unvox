//******************************************************************************
// Module: UnVox
// Author: Sebastian Thiele / Andre Schollmeyer
// 
// Copyright 2019 
// All rights reserved
//******************************************************************************
#include "gl/renderbuffer.hpp"

// system includes
#include <iostream>
#include <cassert>

namespace unvox { namespace gl {

  ///////////////////////////////////////////////////////////////////////////////
  renderbuffer::renderbuffer()
    : _id(0)
  {
    glGenRenderbuffersEXT(1, &_id);
  }


  ///////////////////////////////////////////////////////////////////////////////
  renderbuffer::renderbuffer(GLenum internal_format, std::size_t width, std::size_t height)
    : _id(0)
  {
    glGenRenderbuffersEXT(1, &_id);

    set(internal_format, width, height);
  }


  ///////////////////////////////////////////////////////////////////////////////
  renderbuffer::~renderbuffer()
  {
    glDeleteRenderbuffersEXT(1, &_id);
  }


  ///////////////////////////////////////////////////////////////////////////////
  void
  renderbuffer::bind() const
  {
    glBindRenderbufferEXT(target(), _id);
  }


  ///////////////////////////////////////////////////////////////////////////////
  void
  renderbuffer::unbind() const
  {
    glBindRenderbufferEXT(target(), 0);
  }


  ///////////////////////////////////////////////////////////////////////////////
  bool
  renderbuffer::bound() const
  {
    GLint currently_bound_renderbuffer = 0;
    glGetIntegerv( GL_RENDERBUFFER_BINDING_EXT, &currently_bound_renderbuffer );

    return currently_bound_renderbuffer == int(_id);
  }


  ///////////////////////////////////////////////////////////////////////////////
  void
  renderbuffer::set(GLenum internal_format, std::size_t width, std::size_t height) const
  {
    assert (int(width) <= renderbuffer::get_maxsize() && int(height) <= renderbuffer::get_maxsize());

    bind();
    glRenderbufferStorageEXT(target(), internal_format, GLsizei(width), GLsizei(height) );
    unbind();
  }

  ///////////////////////////////////////////////////////////////////////////////
  void renderbuffer::set(std::size_t samples, GLenum internal_format, std::size_t width, std::size_t height) const
  {
    assert(int(width) <= renderbuffer::get_maxsize() && int(height) <= renderbuffer::get_maxsize());

    glNamedRenderbufferStorageMultisampleEXT(_id, samples, internal_format, width, height);
  }

  ///////////////////////////////////////////////////////////////////////////////
  void renderbuffer::set(std::size_t coverage_samples, size_t color_samples, GLenum internal_format, std::size_t width, std::size_t height) const
  {
    assert(int(width) <= renderbuffer::get_maxsize() && int(height) <= renderbuffer::get_maxsize());
    glNamedRenderbufferStorageMultisampleCoverageEXT(_id, coverage_samples, color_samples, internal_format, width, height);
  }

  ///////////////////////////////////////////////////////////////////////////////
  GLuint renderbuffer::id() const
  {
    return _id;
  }


  ///////////////////////////////////////////////////////////////////////////////
  GLint renderbuffer::get_maxsize()
  {
    GLint max_attach = 0;
    glGetIntegerv( GL_MAX_RENDERBUFFER_SIZE_EXT, &max_attach );
    return max_attach;
  }


  ///////////////////////////////////////////////////////////////////////////////
  GLenum
  renderbuffer::target() const
  {
    return TARGET;
  }

} } // namespace unvox / namespace gl

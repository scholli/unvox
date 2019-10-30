//******************************************************************************
// Module: UnVox
// Author: Sebastian Thiele / Andre Schollmeyer
// 
// Copyright 2019 
// All rights reserved
//******************************************************************************
#ifndef UNVOX_GL_FRAMEBUFFER_OBJECT_HPP
#define UNVOX_GL_FRAMEBUFFER_OBJECT_HPP

#include <iostream>
#include <GL/glew.h>

#include <gl/glpp.hpp>

namespace unvox {
  namespace gl {

    // forward declaration
    class renderbuffer;
    class texture2d;

    class UNVOX_GL framebufferobject 
    {
    public:

	  framebufferobject(framebufferobject const& other) = delete;
	  framebufferobject& operator=(framebufferobject const& other) = delete;

      framebufferobject();
      ~framebufferobject();

    public: // method

      bool              status() const;
      bool              is_framebuffer() const;
      void              print(std::ostream& os) const;

      void              bind() const;
      void              unbind() const;
      bool              bound() const;

      void              attach_texture(texture2d&   texture,
        GLenum       attachment,
        int          miplevel = 0) const;

      void              attach_renderbuffer(renderbuffer const&  renderbuf,
        GLenum               attachment) const;

      void              unattach(GLenum attachment) const;

      static GLuint     max_color_attachments();
      static GLenum     target();
      GLuint            id() const;

    private:

      unsigned _id;
    };



} } // namespace unvox / namespace gl

#endif


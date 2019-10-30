//******************************************************************************
// Module: UnVox
// Author: Sebastian Thiele / Andre Schollmeyer
// 
// Copyright 2019 
// All rights reserved
//******************************************************************************
#ifndef UNVOX_GL_RENDER_BUFFER_HPP
#define UNVOX_GL_RENDER_BUFFER_HPP

// i/f includes
#include <gl/framebufferobject.hpp>

namespace unvox { namespace gl {

  class UNVOX_GL renderbuffer 
  {
    public:

      static GLenum const TARGET = GL_RENDERBUFFER_EXT;

	  renderbuffer(renderbuffer const&) = delete;
	  renderbuffer& operator=(renderbuffer const&) = delete;

      renderbuffer();
      renderbuffer(GLenum internal_format, std::size_t width, std::size_t height);
      ~renderbuffer();

    public :

      void            bind    ( ) const;
      void            unbind  ( ) const;
      bool            bound   ( ) const;

      void            set     (GLenum internal_format, std::size_t width, std::size_t height) const;
      void            set     ( std::size_t samples, GLenum internal_format, std::size_t width, std::size_t height) const;
      void            set     ( std::size_t coverage_samples, size_t color_samples, GLenum internal_format, std::size_t width, std::size_t height) const;
      
      GLuint          id      ( ) const;

      void            print   ( std::ostream& os ) const;

      static GLint    get_maxsize();

      GLenum          target  () const;

  private:

      unsigned _id;
  };

} } // namespace unvox / namespace gl

#endif // UNVOX_GL_RENDER_BUFFER_HPP


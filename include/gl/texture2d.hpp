//******************************************************************************
// Module: UnVox
// Author: Sebastian Thiele / Andre Schollmeyer
// 
// Copyright 2019 
// All rights reserved
//******************************************************************************
#ifndef UNVOX_GL_TEXTURE2D_HPP
#define UNVOX_GL_TEXTURE2D_HPP

// header system
#include <string>

// header project
#include <gl/glpp.hpp>
#include <gl/texture.hpp>

namespace unvox { namespace gl {

  class UNVOX_GL texture2d : public texture
  {
  public :

	  texture2d(texture2d const& other) = delete;
	  texture2d& operator=(texture2d const& other) = delete;

    texture2d                  ( );

    texture2d                  ( std::string const& filename );

    texture2d                  ( std::size_t  width,
                                 std::size_t  height,
                                 GLint        internal_format,
                                 GLenum       format,
                                 GLenum       value_type,
                                 GLint        level = 0,
                                 GLboolean    border = 0 );

    ~texture2d                 ( );

    void            swap       ( texture2d& );


  public : // methods

    bool            load       ( std::string const& filename );

    void            resize     ( std::size_t width,
                                 std::size_t height,
                                 GLint       internal_format);

    void            teximage   ( GLint    level,
                                 GLint    internal_format,
			                           GLsizei  width,
			                           GLsizei  height,
			                           GLint    border,
			                           GLenum   format,
			                           GLenum   type,
			                           GLvoid*  pixels );

    void            texsubimage( GLint    level,
                                 GLint    xoffset,
                                 GLint    yoffset,
			                           GLsizei  width,
			                           GLsizei  height,
			                           GLenum   format,
			                           GLenum   type,
			                           GLvoid*  pixels );

    void            bind       ( );
    void            bind       ( GLint texunit );
    void            bind_as_image ( GLuint imageunit, GLint level, GLboolean layered, GLint layer, GLenum access, GLint format );
    void            unbind     ( );

    void            set_parameteri  ( GLenum pname, GLint value );
    void            set_parameterf  ( GLenum pname, GLfloat value );
    void            set_parameterfv ( GLenum pname, GLfloat const* value );

    GLuint const    id         ( ) const;
    static GLenum   target     ( );

    GLsizei         width       () const;
    GLsizei         height      () const;

  private : // member

    GLuint          _id;
    GLint           _unit;

    GLsizei         _width;
    GLsizei         _height;
};

} } // namespace unvox / namespace gl


#endif // UNVOX_GL_TEXTURE2D_HPP

//******************************************************************************
// Module: UnVox
// Author: Sebastian Thiele / Andre Schollmeyer
// 
// Copyright 2019 
// All rights reserved
//******************************************************************************
#ifndef UNVOX_GL_TEXTURE1D_HPP
#define UNVOX_GL_TEXTURE1D_HPP

// header system
#include <string>

// header project
#include <gl/glpp.hpp>
#include <gl/texture.hpp>

namespace unvox { namespace gl {

  class UNVOX_GL texture1d : public texture
  {
  public :

	  texture1d(texture1d const& other) = delete;
	  texture1d& operator=(texture1d const& other) = delete;

    texture1d                  ( );



    texture1d                  ( std::string const& filename );

    texture1d                  ( std::size_t  width,
                                 GLint        internal_format,
                                 GLenum       format,
                                 GLenum       value_type,
                                 GLint        level = 0,
                                 GLboolean    border = 0 );

    ~texture1d                 ( );

    void            swap       ( texture1d& );


  public : // methods

    bool            load       ( std::string const& in_image_path );

    void            resize     ( std::size_t  width,
                                 GLint        internal_format );

    void            teximage   ( GLint    level,
                                 GLint    internal_format,
			                           GLsizei  width,
			                           GLint    border,
			                           GLenum   format,
			                           GLenum   type,
			                           GLvoid*  pixels );

    void            bind       ( );
    void            bind       ( GLint texunit );
    void            unbind     ( );

    void            set_parameteri  ( GLenum pname, GLint value );
    void            set_parameterf  ( GLenum pname, GLfloat value );
    void            set_parameterfv ( GLenum pname, GLfloat const* value );

    GLuint const    id         ( ) const;
    static GLenum   target     ( );

  private : // member

    GLuint          _id;
    GLint           _unit;

    GLsizei         _width;
};

} } // namespace unvox / namespace gl


#endif // UNVOX_GL_TEXTURE1D_HPP

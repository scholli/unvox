//******************************************************************************
// Module: UnVox
// Author: Sebastian Thiele / Andre Schollmeyer
// 
// Copyright 2019 
// All rights reserved
//******************************************************************************
#ifndef UNVOX_GL_TEXTUREARRAYHPP
#define UNVOX_GL_TEXTUREARRAYHPP

// header system
#include <string>

// header project
#include <gl/glpp.hpp>

namespace unvox { namespace gl {

  class UNVOX_GL texturearray 
  {
  public :

	  texturearray(texturearray const& other) = delete;
	  texturearray& operator=(texturearray const& other) = delete;

    texturearray                  ( );

    texturearray                  ( std::size_t width,
                                    std::size_t height,
                                    std::size_t depth );

    texturearray                  ( std::size_t width,
                                    std::size_t height,
                                    std::size_t depth,
                                    int internal_format,
                                    int format,
                                    int value_type,
                                    int level = 0,
                                    bool border = 0 );

    ~texturearray                  ( );

    void            swap           ( texturearray& );

  public : // methods

    void            teximage       ( GLint    level,
                                     GLint    internal_format,
			                               GLsizei  width,
			                               GLsizei  height,
                                     GLsizei  depth,
			                               GLint    border,
			                               GLenum   format,
			                               GLenum   type,
			                               GLvoid*  pixels );

    void            texsubimage    ( GLint    level,
                                     GLint  	xoffset, 
 	                                   GLint  	yoffset, 
 	                                   GLint  	zoffset, 
			                               GLsizei  width,
			                               GLsizei  height,
                                     GLsizei  depth,
			                               GLenum   format,
			                               GLenum   type,
			                               GLvoid*  data );

    void            bind            ( );
    void            bind            ( GLint texunit );
    void            unbind          ( );

    void            set_parameteri  ( GLenum pname, GLint value );
    void            set_parameterf  ( GLenum pname, GLfloat value );
    void            set_parameterfv ( GLenum pname, GLfloat const* value );

    GLuint const    id           ( ) const;
    static GLenum   target       ( );

  private : // member

    GLuint          _id;
    GLint           _unit;

    std::size_t     _width;
    std::size_t     _height;
    std::size_t     _depth;
};

} } // namespace unvox / namespace gl


#endif // UNVOX_GL_TEXTURE2D_HPP

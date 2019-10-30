//******************************************************************************
// Module: UnVox
// Author: Sebastian Thiele / Andre Schollmeyer
// 
// Copyright 2019 
// All rights reserved
//******************************************************************************
#ifndef UNVOX_GL_TEXTURE3D_HPP
#define UNVOX_GL_TEXTURE3D_HPP

// header system
#include <string>

// header project
#include <gl/glpp.hpp>
#include <gl/texture.hpp>


namespace unvox { namespace gl {

  class UNVOX_GL texture3d : public texture
  {
  public :

	  texture3d(texture3d const& other) = delete;
	  texture3d& operator=(texture3d const& other) = delete;

    texture3d                  ( );



    texture3d                  ( std::string const& filename );

    texture3d                  ( std::size_t  width,
                                 std::size_t  height,
                                 std::size_t  depth,
                                 GLint        internal_format,
                                 GLenum       format,
                                 GLenum       value_type,
                                 GLint        level = 0,
                                 GLboolean    border = 0 );

    ~texture3d                 ( );

    void            swap       ( texture3d& );


  public : // methods

    bool            load       ( std::string const& filename, unsigned depth );

    void            resize     ( std::size_t width,
                                 std::size_t height,
                                 std::size_t depth,
                                 GLint internal_format );

    void            teximage   ( GLint    level,
                                 GLint    internal_format,
			                           GLsizei  width,
			                           GLsizei  height,
                                 GLsizei  depth, 
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
    GLsizei         _height;
    GLsizei         _depth;
};

} } // namespace unvox / namespace gl


#endif // UNVOX_GL_TEXTURE3D_HPP

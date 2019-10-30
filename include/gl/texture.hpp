//******************************************************************************
// Module: UnVox
// Author: Sebastian Thiele / Andre Schollmeyer
// 
// Copyright 2019 
// All rights reserved
//******************************************************************************
#ifndef UNVOX_GL_TEXTURE_HPP
#define UNVOX_GL_TEXTURE_HPP

// header system
#include <string>
#include <map>

// header project
#include <gl/glpp.hpp>

namespace unvox { namespace gl {

  struct UNVOX_GL texture_format 
  {
    texture_format();
    texture_format(GLenum internal_fmt, GLenum base_fmt, std::size_t components_size, GLenum value_type, std::string const& as_string);
    GLenum        internal_format;
    GLenum        base_format;
    std::size_t   size;
    GLenum        type;
    std::string   name;
  };

  class UNVOX_GL texture
  {
  public :

    texture                                       ( );
    ~texture                                      ( );

    std::size_t             size_of_format        ( GLenum internal_format );
    GLenum                  base_format           ( GLenum internal_format );
    GLenum                  value_type_of_format  ( GLenum internal_format );
    std::string             name                  ( GLenum internal_format );

  public : // methods

    virtual void            bind                  ( GLint texunit ) = 0;
    virtual void            unbind                ( ) = 0;
    virtual GLuint const    id                    ( ) const = 0;

  private : // methods

    void                    _init                 ();

  private : // member

};

} } // namespace unvox / namespace gl


#endif // UNVOX_GL_TEXTURE1D_HPP

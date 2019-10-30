//******************************************************************************
// Module: UnVox
// Author: Sebastian Thiele / Andre Schollmeyer
// 
// Copyright 2019 
// All rights reserved
//******************************************************************************
#ifndef UNVOX_GL_CUBEMAP_HPP
#define UNVOX_GL_CUBEMAP_HPP

// header system
#include <string>

// header project
#include <gl/glpp.hpp>
#include <gl/texture.hpp>

namespace unvox { namespace gl {

  class UNVOX_GL cubemap : public texture
  {
  private : // non-copyable

	  cubemap(cubemap const&) = delete;
	  cubemap& operator=(cubemap const& other) = delete;

  public :
    
    cubemap                 ( );
    ~cubemap                ( );
    void          swap      ( cubemap& );

  public : // methods

    void          load      ( std::string const& imgfile_posx,
                              std::string const& imgfile_negx,
                              std::string const& imgfile_posy,
                              std::string const& imgfile_negy,
                              std::string const& imgfile_posz,
                              std::string const& imgfile_negz );

    GLuint const  id        ( ) const override;

    void          bind      ( );

    void          bind      ( GLint texunit );

    void          unbind    ( );

    void          enable    ( ) const;

    void          disable   ( ) const;
    
    void          parameter ( GLenum pname, int param );

    static GLenum target    ( );

  private : // methods

    void          openfile_ ( std::string const&  filename, 
                              GLenum              target );

  private : // members

    GLuint        id_;
    GLint         unit_;
  };

} } // namespace unvox / namespace gl

#endif // UNVOX_GL_CUBEMAP_HPP

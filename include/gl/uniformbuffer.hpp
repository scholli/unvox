//******************************************************************************
// Module: UnVox
// Author: Sebastian Thiele / Andre Schollmeyer
// 
// Copyright 2019 
// All rights reserved
//******************************************************************************
#ifndef UNVOX_GL_UNIFORM_BUFFER_HPP
#define UNVOX_GL_UNIFORM_BUFFER_HPP

// header system
#include <string>

// header project
#include <gl/glpp.hpp>
#include <gl/buffer.hpp>


namespace unvox { namespace gl {

class UNVOX_GL uniformbuffer : public buffer
{
public :
  
  uniformbuffer                  ( );

  uniformbuffer                  ( std::size_t bytes, GLenum usage );

  ~uniformbuffer                 ( );

  uniformbuffer& operator=       ( uniformbuffer const& );

  void            swap           ( uniformbuffer& );

public : // methods

  // bind and unbind arraybuffer

  /* virtual */ void    bind     ( ) const;
  /* virtual */ void    unbind   ( ) const;

  void                  bindbase ( GLuint base ) const;

  /* virtual */ GLenum  target   () const;
  
private : // attibutes

};

} } // namespace unvox / namespace gl

#endif // UNVOX_GL_UNIFORM_BUFFER_HPP

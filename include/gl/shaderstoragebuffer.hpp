//******************************************************************************
// Module: UnVox
// Author: Sebastian Thiele / Andre Schollmeyer
// 
// Copyright 2019 
// All rights reserved
//******************************************************************************
#ifndef UNVOX_GL_SHADER_STORAGE_BUFFER_HPP
#define UNVOX_GL_SHADER_STORAGE_BUFFER_HPP

// header system
#include <string>

// header project
#include <gl/glpp.hpp>
#include <gl/buffer.hpp>


namespace unvox { namespace gl {

class UNVOX_GL shaderstoragebuffer : public buffer
{
public :
  
  shaderstoragebuffer();

  shaderstoragebuffer(std::size_t bytes, GLenum usage = GL_STATIC_DRAW);

  ~shaderstoragebuffer();

  void            swap(shaderstoragebuffer&);

public : // methods

  /* virtual */ void    bind   ( ) const;

  /* virtual */ void    unbind ( ) const;

  /* virtual */ GLenum  target ( ) const;
 
private : // members

};

} } // namespace unvox / namespace gl

#endif // UNVOX_GL_SHADER_STORAGE_BUFFER_HPP

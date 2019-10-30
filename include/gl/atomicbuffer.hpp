//******************************************************************************
// Module: UnVox
// Author: Sebastian Thiele / Andre Schollmeyer
// 
// Copyright 2019 
// All rights reserved
//******************************************************************************
#ifndef UNVOX_GL_ATOMIC_BUFFER_HPP
#define UNVOX_GL_ATOMIC_BUFFER_HPP

// header system
#include <string>

// header project
#include <gl/glpp.hpp>
#include <gl/buffer.hpp>


namespace unvox { namespace gl {

  class UNVOX_GL atomicbuffer : public buffer
{
public :
  
  atomicbuffer();

  atomicbuffer(std::size_t bytes, GLenum usage = GL_STATIC_DRAW);

  ~atomicbuffer();

  void            swap(atomicbuffer&);

public : // methods

  /* virtual */ void    bind   ( ) const;

  void bind_buffer_range(unsigned binding_point, unsigned offset, unsigned count) const;
  void bind_buffer_base(unsigned binding_point) const;

  /* virtual */ void    unbind ( ) const;

  /* virtual */ GLenum  target ( ) const;
 
private : // members

};

} } // namespace unvox / namespace gl

#endif // UNVOX_GL_ATOMIC_BUFFER_HPP

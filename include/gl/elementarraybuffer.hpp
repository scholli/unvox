//******************************************************************************
// Module: UnVox
// Author: Sebastian Thiele / Andre Schollmeyer
// 
// Copyright 2019 
// All rights reserved
//******************************************************************************
#ifndef UNVOX_GL_ELEMENT_ARRAY_HPP
#define UNVOX_GL_ELEMENT_ARRAY_HPP

// header system
#include <string>

// header project
#include <gl/glpp.hpp>
#include <gl/buffer.hpp>

namespace unvox { namespace gl {

  class UNVOX_GL elementarraybuffer : public buffer 
{
public :
  
  elementarraybuffer                  ( );

  elementarraybuffer                  ( std::size_t bytes, GLenum usage );

  ~elementarraybuffer                 ( );
  
  void            swap                ( elementarraybuffer& );

public : // methods


  /* virtual */ void    bind          ( ) const;
  
  /* virtual */ void    unbind        ( ) const;

  /* virtual */ GLenum  target        ( ) const;
 

private : // attributes

};

} } // namespace unvox / namespace gl

#endif // UNVOX_GL_ELEMENT_ARRAY_HPP

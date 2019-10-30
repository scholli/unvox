//******************************************************************************
// Module: UnVox
// Author: Sebastian Thiele / Andre Schollmeyer
// 
// Copyright 2019 
// All rights reserved
//******************************************************************************
#ifndef UNVOX_GL_VERTEX_ARRAY_OBJECT_HPP
#define UNVOX_GL_VERTEX_ARRAY_OBJECT_HPP

// header system
#include <string>

// header project
#include <gl/glpp.hpp>




namespace unvox { namespace gl {

  class buffer;

class UNVOX_GL vertexarrayobject
{
public :
  
  vertexarrayobject                  ( );
  ~vertexarrayobject                 ( );

public : // methods

  void            bind            ( ) const;
  void            unbind          ( ) const;

  void            enable_attrib   ( std::size_t index ) const;
  void            disable_attrib  ( std::size_t index ) const;
  
  void            attrib_array    ( buffer const&         buf, 
                                    std::size_t           index, 
                                    std::size_t           size, 
                                    GLenum                type, 
                                    bool                  normalize,
                                    std::size_t           stride, 
                                    std::size_t           offset ) const;

private : // members

  GLuint          _id;
};

} } // namespace unvox / namespace gl

#endif // UNVOX_GL_ARRAY_BUFFER_HPP

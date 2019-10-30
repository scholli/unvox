//******************************************************************************
// Module: UnVox
// Author: Sebastian Thiele / Andre Schollmeyer
// 
// Copyright 2019 
// All rights reserved
//******************************************************************************
#ifndef UNVOX_GL_TRANSFORMFEEDBACK_BUFFER_HPP
#define UNVOX_GL_TRANSFORMFEEDBACK_BUFFER_HPP

// header system
#include <string>
#include <memory>
#include <vector>
#include <cassert>

// header project
#include <gl/glpp.hpp>
#include <gl/buffer.hpp>
#include <gl/vertexarrayobject.hpp>
#include <gl/arraybuffer.hpp>



namespace unvox { namespace gl {

class UNVOX_GL transform_feedback
{
public :
  
  transform_feedback();
  ~transform_feedback();

  void            swap         (transform_feedback& );

public : // methods

  bool                        active() const;
  GLenum                      captured_primitive_type() const;

  /* virtual */ void          bind   ( ) const;
  /* virtual */ void          unbind ( ) const;

  void                        begin(GLenum primitive_type);
  void                        end();

  unsigned                    id() const;

private : // members

  unsigned                    _gl_object_id;
  int                         _gl_object_target;
  int                         _gl_object_binding;
  bool                        _active;
  GLenum                      _primitive_type;

};

struct transform_feedback_buffer {
  std::shared_ptr<unvox::gl::transform_feedback> feedback;
  std::shared_ptr<unvox::gl::vertexarrayobject>  vertex_array_object;
  std::shared_ptr<unvox::gl::arraybuffer>        buffer;
};

} } // namespace unvox / namespace gl

#endif // UNVOX_GL_ARRAY_BUFFER_HPP

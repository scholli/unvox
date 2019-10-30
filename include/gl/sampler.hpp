//******************************************************************************
// Module: UnVox
// Author: Sebastian Thiele / Andre Schollmeyer
// 
// Copyright 2019 
// All rights reserved
//******************************************************************************
#ifndef UNVOX_GL_SAMPLER_HPP
#define UNVOX_GL_SAMPLER_HPP

#if WIN32
  #pragma warning(disable: 4996) // unsafe std::copy
#endif

// header system

// header project
#include <gl/glpp.hpp>


namespace unvox { namespace gl {

class UNVOX_GL sampler 
{
public : // c'tor, d'tor

  sampler(sampler const& other) = delete;
  sampler& operator=(sampler const& other) = delete;

  sampler                         ();
  virtual ~sampler                ();

public : // methods

  void            swap            ( sampler& );

  void            parameter       ( GLenum pname,
                                    GLint  param ) const;

  void            parameter       ( GLenum  pname,
                                    GLfloat param ) const;

  void            bind            ( GLint unit ) const;
  void            unbind          () const;

private : // members

  GLuint          _id;
};

} } // namespace unvox / namespace gl

#endif // UNVOX_GL_SAMPLER_HPP

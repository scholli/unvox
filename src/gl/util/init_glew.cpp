//******************************************************************************
// Module: UnVox
// Author: Sebastian Thiele / Andre Schollmeyer
// 
// Copyright 2019 
// All rights reserved
//******************************************************************************
// include i/f header
#include "gl/util/init_glew.hpp"

#include <stdexcept>

namespace unvox { namespace gl {

/////////////////////////////////////////////////////////////////////////////
void init_glew ( std::ostream& os )
{
  glewExperimental = true;
  GLenum err = glewInit();

  if (GLEW_OK != err) {
    os << "glewInit() failed" << std::endl;
    throw std::runtime_error("Could not initialize glew. GL Context ready?");
  } else {
    os << "glewInit() ok" << std::endl;

    // clear INVALID_ENUM error from stack
    err = glGetError();
  }
}

} } // namespace unvox / namespace gl


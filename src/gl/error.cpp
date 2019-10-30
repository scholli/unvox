//******************************************************************************
// Module: UnVox
// Author: Sebastian Thiele / Andre Schollmeyer
// 
// Copyright 2019 
// All rights reserved
//******************************************************************************
// header i/f
#include "gl/error.hpp"

// header, system
#include <iostream>
#include <GL/glew.h>

namespace unvox { namespace gl {

bool
error(std::string const& message)
{
  GLenum err = glGetError();

  std::cerr << message << " : ";

  switch (err) {

    case GL_NO_ERROR :
		std::cerr << "no error.\n";
      return true;

    case GL_INVALID_ENUM :
		std::cerr << "GL_INVALID_ENUM" << std::endl;
      return false;

    case GL_INVALID_VALUE :
      std::cerr << "GL_INVALID_VALUE" << std::endl;
      return false;

    case GL_INVALID_OPERATION :
      std::cerr << "GL_INVALID_OPERATION" << std::endl;
      return false;

    case GL_STACK_OVERFLOW :
      std::cerr << "GL_STACK_OVERFLOW" << std::endl;
      return false;

    case GL_STACK_UNDERFLOW :
      std::cerr << "GL_STACK_UNDERFLOW" << std::endl;
      return false;

    case GL_OUT_OF_MEMORY :
      std::cerr << "GL_OUT_OF_MEMORY" << std::endl;
      return false;

    case GL_TABLE_TOO_LARGE :
      std::cerr << "GL_TABLE_TOO_LARGE" << std::endl;
      return false;

    case GL_INVALID_FRAMEBUFFER_OPERATION_EXT :
      std::cerr << "GL_INVALID_FRAMEBUFFER_OPERATION_EXT" << std::endl;
      return false;

    default :
      std::cerr << "unknwon error.\n";
      return false;
  };
}

} } // namespace unvox / namespace gl

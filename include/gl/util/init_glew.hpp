//******************************************************************************
// Module: UnVox
// Author: Sebastian Thiele / Andre Schollmeyer
// 
// Copyright 2019 
// All rights reserved
//******************************************************************************
#ifndef UNVOX_GL_INIT_GLEW_HPP
#define UNVOX_GL_INIT_GLEW_HPP

#include <iostream>

#include <gl/glpp.hpp>

namespace unvox { namespace gl {

UNVOX_GL void init_glew ( std::ostream& log_os = std::cout );

} } // namespace unvox / namespace gl

#endif // UNVOX_GL_INIT_GLEW_HPP

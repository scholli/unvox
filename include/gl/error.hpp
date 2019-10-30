//******************************************************************************
// Module: UnVox
// Author: Sebastian Thiele / Andre Schollmeyer
// 
// Copyright 2019 
// All rights reserved
//******************************************************************************
#ifndef UNVOX_GL_ERROR_HPP
#define UNVOX_GL_ERROR_HPP

#include <string>

#include <gl/glpp.hpp>

namespace unvox { namespace gl {

  UNVOX_GL extern bool error(std::string const& message);

} } // namespace unvox / namespace gl

#endif // UNVOX_GL_GLSTATE_HPP

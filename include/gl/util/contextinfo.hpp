//******************************************************************************
// Module: UnVox
// Author: Sebastian Thiele / Andre Schollmeyer
// 
// Copyright 2019 
// All rights reserved
//******************************************************************************
#ifndef UNVOX_GL_CONTEXTINFO_HPP
#define UNVOX_GL_CONTEXTINFO_HPP

#include <cstdlib>
#include <iostream>
#include <string>

#if WIN32
  #pragma warning(disable: 4245)
#endif

#include <gl/glpp.hpp>

namespace unvox { namespace gl {

UNVOX_GL void print_contextinfo  ( std::ostream& os );
UNVOX_GL void print_extensions   ( std::ostream& os );
UNVOX_GL void print_memory_usage ( std::ostream& os );
UNVOX_GL bool check_extension    ( std::string const& extension_name );

} } // namespace unvox / namespace gl

#endif // UNVOX_GL_HUTILS_HPP

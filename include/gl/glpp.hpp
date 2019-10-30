//******************************************************************************
// Module: UnVox
// Author: Sebastian Thiele / Andre Schollmeyer
// 
// Copyright 2019 
// All rights reserved
//******************************************************************************
#ifndef UNVOX_GL_HPP
#define UNVOX_GL_HPP

#include <GL/glew.h>

// disable glut/STL warnings
#ifdef WIN32
  #pragma warning(disable:4251) // dll-interface for stl container
  #pragma warning(disable:4275) // non dll-interface for boost::noncopyable
  #pragma warning(disable:4996) // std::copy unsafe
  #pragma warning(disable:4505) // glutInit_ATEXIT_HACK unreferenced local function has been removed
  #pragma warning(disable:4351) // default initialisation of array
#endif

#ifdef WIN32
  // disable openCL warnings
  #pragma warning(disable:4610) // can never be instantiated
  #pragma warning(disable:4512) // assignment operator could not be constructed
  #pragma warning(disable:4510) // deafult c'tor could not be constructed
  #pragma warning(disable:4482) // Qt::Mousebutton
  #pragma warning(disable:4100) // unreferenced parameter
#endif

#ifdef WIN32
//  #if UNVOX_GL_EXPORT
//    #define UNVOX_GL __declspec(dllexport)
//  #else
//    #define UNVOX_GL __declspec(dllimport)
//  #endif
//#else
  #define UNVOX_GL
#endif

#define UNVOX_GL_DIRECT_STATE_ACCESS 1

#endif // UNVOX_GL_HPP

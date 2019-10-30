//******************************************************************************
// Module: UnVox
// Author: Sebastian Thiele / Andre Schollmeyer
// 
// Copyright 2019 
// All rights reserved
//******************************************************************************
#pragma once

#include <application.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

class gui_glfw
{
public :

  gui_glfw(GLFWwindow* window, std::string const& glsl_version);
  ~gui_glfw();

public:

  void process(application::configuration& config);
  void show();
  void close();

private : 

  void _definition(application::configuration& config);

private:

  GLFWwindow* _window;
};
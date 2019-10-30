//******************************************************************************
// Module: UnVox
// Author: Sebastian Thiele / Andre Schollmeyer
// 
// Copyright 2019 
// All rights reserved
//******************************************************************************
#include "gui_glfw.hpp"

#include <GLFW/glfw3.h>

///////////////////////////////////////////////////////////////////////////////
gui_glfw::gui_glfw(GLFWwindow* window, std::string const& glsl_version)
  : _window(window)
{
  // Setup Dear ImGui binding
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;
  //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
  //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(glsl_version.c_str());

  // Setup style
  ImGui::StyleColorsDark();
}

///////////////////////////////////////////////////////////////////////////////
gui_glfw::~gui_glfw() 
{}

///////////////////////////////////////////////////////////////////////////////
void gui_glfw::process(application::configuration& config)
{
  // draw gui on top
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  _definition(config);

  ImGui::Render();
  
  show();
}

///////////////////////////////////////////////////////////////////////////////
void gui_glfw::show() 
{
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

///////////////////////////////////////////////////////////////////////////////
void gui_glfw::close() 
{
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

///////////////////////////////////////////////////////////////////////////////
void gui_glfw::_definition(application::configuration& config)
{
  ImGui::Begin("Configuration");

  ImGui::Text("This is example GUI. Press 'g' to en/disable.");
  ImGui::Checkbox("Draw plane", &config.enable_draw);

  ImGui::SliderFloat("Size", &config.size, 0.0f, 1.0f);
  ImGui::ColorEdit3("Background Color", (float*)&config.background);

  if (ImGui::Button("Random Background Color")) {
    std::srand(int(ImGui::GetIO().Framerate));
    config.background.x = float(std::rand()) / RAND_MAX;
    config.background.y = float(std::rand()) / RAND_MAX;
    config.background.z = float(std::rand()) / RAND_MAX;
  }

  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
  ImGui::End();
}
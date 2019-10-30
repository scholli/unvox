//******************************************************************************
// Module: UnVox
// Author: Sebastian Thiele / Andre Schollmeyer
// 
// Copyright 2019 
// All rights reserved
//******************************************************************************
#pragma once

#include <memory>
#include <string>

#include <glm/glm.hpp>

#include <gl/arraybuffer.hpp>
#include <gl/vertexarrayobject.hpp>
#include <gl/shader.hpp>
#include <gl/program.hpp>

struct GLFWwindow;

class application {

private:

  std::shared_ptr<unvox::gl::program>           _program;
  std::shared_ptr<unvox::gl::vertexarrayobject> _plane;
  std::shared_ptr<unvox::gl::arraybuffer>       _vertices;
  std::shared_ptr<unvox::gl::arraybuffer>       _texcoords;

public:

  struct configuration {
    int counter = 0;
    bool enable_draw = true;
    float size = 1.0f;
    glm::vec4 background = {0,0,0,0};

    int window_width;
    int window_height;
  };

  configuration config;

public :

  application(GLFWwindow* window);

  std::string read_from_file(std::string const& filename);
  void init_program();
  void init_plane();
  void display();

};

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void motion_callback(GLFWwindow* window, double x, double y);
void size_callback(GLFWwindow* window, int x, int y);
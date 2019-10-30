//******************************************************************************
// Module: UnVox
// Author: Sebastian Thiele / Andre Schollmeyer
// 
// Copyright 2019 
// All rights reserved
//******************************************************************************
#include "application.hpp"

#include <sstream>
#include <iostream>

#include <GLFW/glfw3.h>

///////////////////////////////////////////////////////////////////////////////
application::application(GLFWwindow* window)
{
  init_program();
  init_plane();

  glfwGetWindowSize(window, &config.window_width, &config.window_height);
}

///////////////////////////////////////////////////////////////////////////////
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }
}

///////////////////////////////////////////////////////////////////////////////
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
  switch (button) {
  case GLFW_MOUSE_BUTTON_LEFT:
    std::cout << "left button ";
    break;
  case GLFW_MOUSE_BUTTON_RIGHT:
    std::cout << "right button ";
    break;
  case GLFW_MOUSE_BUTTON_MIDDLE:
    std::cout << "middle button ";
    break;
  }

  switch (action) {
  case GLFW_RELEASE:
    std::cout << "released." << std::endl;
    break;
  case GLFW_PRESS:
    std::cout << "pressed." << std::endl;
    break;
  }
}

///////////////////////////////////////////////////////////////////////////////
void motion_callback(GLFWwindow* window, double x, double y)
{
  //std::cout << "Cursor movement : Position = [" << x << "," << y << "]" << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
void size_callback(GLFWwindow* window, int x, int y)
{
  application* app = reinterpret_cast<application*>(glfwGetWindowUserPointer(window));

  app->config.window_width = x;
  app->config.window_height = y;
  std::cout << "Resize to [" << x << "," << y << "]" << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
std::string application::read_from_file(std::string const& filename)
{
  std::ifstream source_str(filename, std::ios_base::in);
  if (source_str) {
    std::stringstream ss;
    ss << source_str.rdbuf();
    std::string source_code = ss.str();
    return source_code;
  }
  else {
    throw std::runtime_error(std::string("Could not open file: ") + filename);
  }
}

///////////////////////////////////////////////////////////////////////////////
void application::init_program()
{
  unvox::gl::shader vs(unvox::gl::vertex_stage);
  unvox::gl::shader fs(unvox::gl::fragment_stage);

  vs.load("vshader.glsl");
  fs.load("fshader.glsl");

    if (!vs.compile()) {
        std::cerr << vs.log();
    }
    if (!fs.compile()) {
        std::cerr << fs.log();
    }

  _program.reset(new unvox::gl::program);

  _program->add(&vs);
  _program->add(&fs);
  _program->link();
}

///////////////////////////////////////////////////////////////////////////////
void application::init_plane()
{
    _plane.reset(new unvox::gl::vertexarrayobject);
    _vertices.reset(new unvox::gl::arraybuffer);
    _texcoords.reset(new unvox::gl::arraybuffer);

    // bind the VAO for the plahe
    _plane->bind();

    GLfloat triangle_verts[12] = { -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f };
    GLfloat triangle_tc[12] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f };

    // bind the VBO for the triangle vertices
    _vertices->bind();
    _vertices->bufferdata(sizeof(triangle_verts), triangle_verts, GL_STATIC_DRAW);

    _texcoords->bind();
    _texcoords->bufferdata(sizeof(triangle_verts), triangle_verts, GL_STATIC_DRAW);

    _plane->enable_attrib(0);
    _plane->enable_attrib(1);

    _vertices->bind_base(0);
    _texcoords->bind_base(1);

    _plane->unbind();
}

///////////////////////////////////////////////////////////////////////////////
void application::display()
{
  glClearColor(config.background.x, config.background.y, config.background.z, config.background.w);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  _program->bind_attrib_location("Position", 0);
  _program->bind_attrib_location("Texcoord", 1);

  glDrawArrays(GL_TRIANGLES, 0, 6);
}

//******************************************************************************
// Module: UnVox
// Author: Sebastian Thiele / Andre Schollmeyer
// 
// Copyright 2019 
// All rights reserved
//******************************************************************************

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <functional>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <gui_glfw.hpp>

#include <glm/glm.hpp>

#include "application.hpp"
#include "gui_glfw.hpp"

///////////////////////////////////////////////////////////////////////////////
// configuration
///////////////////////////////////////////////////////////////////////////////
int window_width = 1920;
int window_height = 1080;
const std::string window_title = "GLFW Template";

///////////////////////////////////////////////////////////////////////////////
// error handling
///////////////////////////////////////////////////////////////////////////////
void error_callback(int, const char * message)
{
  throw std::runtime_error(message);
}

///////////////////////////////////////////////////////////////////////////////
std::string get_glew_error_name(GLenum err) {
  std::stringstream ss;
  ss << glewGetErrorString(err);
  std::string message;
  std::getline(ss, message);
  return message;
}

///////////////////////////////////////////////////////////////////////////////
void check_gl_error() {
  GLenum err;
  while ((err = glGetError()) != GL_NO_ERROR)
  {
    switch (err) {
    case GL_INVALID_ENUM: std::cout << "GL_INVALID_ENUM" << std::endl; break;
    case GL_INVALID_VALUE: std::cout << "GL_INVALID_VALUE" << std::endl; break;
    case GL_INVALID_OPERATION: std::cout << "GL_INVALID_OPERATION" << std::endl; break;
    case GL_STACK_OVERFLOW: std::cout << "GL_STACK_OVERFLOW" << std::endl; break;
    case GL_STACK_UNDERFLOW: std::cout << "GL_STACK_UNDERFLOW" << std::endl; break;
    case GL_OUT_OF_MEMORY: std::cout << "GL_OUT_OF_MEMORY" << std::endl; break;
    case GL_INVALID_FRAMEBUFFER_OPERATION: std::cout << "GL_INVALID_FRAMEBUFFER_OPERATION" << std::endl; break;
    case GL_CONTEXT_LOST: std::cout << "GL_CONTEXT_LOST" << std::endl; break;
    case GL_TABLE_TOO_LARGE: std::cout << "GL_TABLE_TOO_LARGE" << std::endl; break;
    }
  }
}





///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
int main()
{
  try {
    // init context
    if (!glfwInit())
    {
      throw std::runtime_error("Failed to init GLFW.");
    }

    // configure window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create window
    GLFWwindow* window = glfwCreateWindow(window_width, window_height, window_title.c_str(), NULL, NULL);
    if (!window)
    {
      throw std::runtime_error("window or context creation failed.");
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);

    // retrieve GL API
    glewExperimental = true;
    const GLenum err = glewInit();

    if (GLEW_OK != err)
    {
      throw std::runtime_error(get_glew_error_name(err));
    }

    glGetError();

    // fps counter
    unsigned int frame_count = 0;
    double last_frametime = glfwGetTime();

    check_gl_error();
    std::cout << "Do not ignore GL errors after this point.\n" << std::endl;

    application app(window);
    gui_glfw    gui(window, "#version 460");

    using namespace std::placeholders;

    // setting callbacks
    glfwSetWindowSizeCallback(window, &size_callback);
    glfwSetKeyCallback(window, &key_callback);
    glfwSetMouseButtonCallback(window, &mouse_button_callback);
    glfwSetCursorPosCallback(window, &motion_callback);
    glfwSetErrorCallback(error_callback);
    glfwSetWindowUserPointer(window, (void*)(&app));

    // start mainloop
    while (!glfwWindowShouldClose(window))
    {
      double current_frametime = glfwGetTime();
      ++frame_count;

      // draw plane
      app.display();

      // input handling
      glfwPollEvents();

      gui.process(app.config);

      glfwMakeContextCurrent(window);
      glfwSwapBuffers(window);
    }
    
    gui.close();

    // if everything is done. clean up.
    glfwDestroyWindow(window);
    glfwTerminate();

    return EXIT_SUCCESS;
  }
  catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    system("pause");
    return EXIT_FAILURE;
  }
}
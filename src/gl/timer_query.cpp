//******************************************************************************
// Module: UnVox
// Author: Sebastian Thiele / Andre Schollmeyer
// 
// Copyright 2019 
// All rights reserved
//******************************************************************************
#include "gl/timer_query.hpp"
#include "gl/error.hpp"

// header system
#include <chrono>
#include <iostream>
#include <GL/glew.h>

namespace unvox { namespace gl {

////////////////////////////////////////////////////////////////////////////////
void timer_query::begin() {
  _result_fetched = false;
  glBeginQuery(GL_TIME_ELAPSED, id());
}

////////////////////////////////////////////////////////////////////////////////
void timer_query::end() {  
  glEndQuery(GL_TIME_ELAPSED);
}

////////////////////////////////////////////////////////////////////////////////
bool timer_query::result_fetched() const
{
  return _result_fetched;
}

////////////////////////////////////////////////////////////////////////////////
double timer_query::time_in_ms(bool wait, double timeout_ms) 
{
  if (wait) {
    auto start = std::chrono::system_clock::now();

    while (!is_available())
    {
      auto end = std::chrono::system_clock::now();
      auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
      if (elapsed.count() > timeout_ms) {
        std::cout << "timer_query::time_in_ms(): Time out reached.";
        _result_fetched = true;
        return 0.0;
      } 
    };
  }
  GLuint64 result = 0;
  glGetQueryObjectui64v(id(), GL_QUERY_RESULT, &result);
  _result_fetched = true;
  return double(result) / double(1000000);
}

} } // namespace unvox / namespace gl

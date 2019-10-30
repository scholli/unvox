//******************************************************************************
// Module: UnVox
// Author: Sebastian Thiele / Andre Schollmeyer
// 
// Copyright 2019 
// All rights reserved
//******************************************************************************
#include "gl/transformfeedback_query.hpp"
#include "gl/error.hpp"

// header system
#include <GL/glew.h>

namespace unvox {
  namespace gl {

    ////////////////////////////////////////////////////////////////////////////////
    void transformfeedback_query::begin() {
      glBeginQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN, id());
    }

    ////////////////////////////////////////////////////////////////////////////////
    void transformfeedback_query::end() {
      glEndQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN);
    }

    ////////////////////////////////////////////////////////////////////////////////
    long long transformfeedback_query::primitives_written(bool wait) const {
      if (wait) {
        while (is_available() == false) {}
      }
      GLuint64 result = 0;
      glGetQueryObjectui64v(id(), GL_QUERY_RESULT, &result);
      return result;
    }

  }
} // namespace unvox / namespace gl

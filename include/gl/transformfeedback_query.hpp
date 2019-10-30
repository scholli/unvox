//******************************************************************************
// Module: UnVox
// Author: Sebastian Thiele / Andre Schollmeyer
// 
// Copyright 2019 
// All rights reserved
//******************************************************************************
#ifndef UNVOX_GL_TRANSFORMFEEDBACK_QUERY_HPP
#define UNVOX_GL_TRANSFORMFEEDBACK_QUERY_HPP

// header system
#include <string>
#include <map>

// header project
#include <gl/glpp.hpp>
#include <gl/query.hpp>

namespace unvox {
  namespace gl {

    class UNVOX_GL transformfeedback_query : public query
    {
    public: // methods

      /*virtual*/ void begin() override;
      /*virtual*/ void end() override;

      long long primitives_written(bool wait = true) const; // in ms

    private: // member

    };

  }
} // namespace unvox / namespace gl


#endif // UNVOX_GL_TRANSFORMFEEDBACK_QUERY_HPP

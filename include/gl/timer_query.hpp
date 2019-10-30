//******************************************************************************
// Module: UnVox
// Author: Sebastian Thiele / Andre Schollmeyer
// 
// Copyright 2019 
// All rights reserved
//******************************************************************************
#ifndef UNVOX_GL_TIMER_QUERY_HPP
#define UNVOX_GL_TIMER_QUERY_HPP

// header system
#include <string>
#include <map>

// header project
#include <gl/glpp.hpp>
#include <gl/query.hpp>

namespace unvox { namespace gl {

  class UNVOX_GL timer_query : public query
  {
  public : // methods

    /*virtual*/ void begin() override;
    /*virtual*/ void end() override;

    double time_in_ms(bool wait = true, double timeout_ms = 1000); // in ms
    bool   result_fetched() const;

  private : // member
    bool _result_fetched = true;
};

} } // namespace unvox / namespace gl


#endif // UNVOX_GL_QUERY_HPP

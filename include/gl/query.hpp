//******************************************************************************
// Module: UnVox
// Author: Sebastian Thiele / Andre Schollmeyer
// 
// Copyright 2019 
// All rights reserved
//******************************************************************************
#ifndef UNVOX_GL_QUERY_HPP
#define UNVOX_GL_QUERY_HPP

// header system
#include <string>
#include <map>

// header project
#include <gl/glpp.hpp>

namespace unvox { namespace gl {

  class UNVOX_GL query
  {
  public :

    query();
    ~query();

  public : // methods

    unsigned id() const;

    void         reset();
    virtual void begin() = 0;
    virtual void end() = 0;
    virtual bool is_available() const;

  private : // member

    unsigned _id;
};

} } // namespace unvox / namespace gl


#endif // UNVOX_GL_QUERY_HPP

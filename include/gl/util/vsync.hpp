/********************************************************************************
* 
* Copyright (C) 2011 Bauhaus-Universitaet Weimar                                               
*
*********************************************************************************
*
*  module     : vsync.hpp                                        
*  project    : glpp 
*  description: 
*
********************************************************************************/
#ifndef UNVOX_GL_VSYNC_HPP
#define UNVOX_GL_VSYNC_HPP

#include <gl/glpp.hpp>

namespace unvox { namespace gl {

UNVOX_GL bool set_vsync ( bool enable );
UNVOX_GL bool get_vsync ( bool& vsync );

} } // namespace unvox / namespace gl

#endif // UNVOX_GL_VSYNC_HPP

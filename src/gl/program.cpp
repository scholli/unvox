//******************************************************************************
// Module: UnVox
// Author: Sebastian Thiele / Andre Schollmeyer
// 
// Copyright 2019 
// All rights reserved
//******************************************************************************
#include "gl/program.hpp"

#include <gl/atomicbuffer.hpp>
#include <gl/texturebuffer.hpp>
#include <gl/shaderstoragebuffer.hpp>
#include <gl/uniformbuffer.hpp>
#include <gl/texture1d.hpp>
#include <gl/texture2d.hpp>
#include <gl/texture3d.hpp>
#include <gl/texturearray.hpp>
#include <gl/cubemap.hpp>
#include <gl/error.hpp>

// header, system
#include <iostream>
#include <GL/glew.h>


namespace unvox { namespace gl {

////////////////////////////////////////////////////////////////////////////////
program::program()
: is_linked_(false)
{
  id_ = glCreateProgram();
}


////////////////////////////////////////////////////////////////////////////////
program::~program()
{
  glDeleteProgram(id_);
}


////////////////////////////////////////////////////////////////////////////////
void
program::add(shader* shader)
{
  glAttachShader(id_, shader->id());
}


////////////////////////////////////////////////////////////////////////////////
void
program::remove(shader* shader)
{
  glDetachShader(id_, shader->id());
}


////////////////////////////////////////////////////////////////////////////////
void
program::link()
{
  glLinkProgram(id_);

  glGetProgramiv(id_, GL_LINK_STATUS, &is_linked_);

  if (is_linked_ != GL_TRUE)
  {
    std::cerr << "Linking program failed." << std::endl;
    std::cerr << log() << std::endl;
  }
  else {
    std::cout << "Linking program succeed." << std::endl;
  }

  //assert(is_linked_ && "program::link() : assertion when linking program");
}


////////////////////////////////////////////////////////////////////////////////
void
program::begin() const
{
  glUseProgram(id_);
}


////////////////////////////////////////////////////////////////////////////////
void
program::end() const
{
  glUseProgram(0);
}


////////////////////////////////////////////////////////////////////////////////
GLuint program::id() const
{
  return id_;
}


////////////////////////////////////////////////////////////////////////////////
std::string 
program::log() const
{
  GLint log_len;
  glGetProgramiv(id_, GL_INFO_LOG_LENGTH, &log_len);

  GLint size;
  char* buf = new char[log_len];

  glGetProgramInfoLog(id_, log_len, &size, buf);

  std::string infolog(buf);
  delete[] buf;

  return infolog;
}


////////////////////////////////////////////////////////////////////////////////
void
program::set_uniform1f(char const* varname, GLfloat v0) const
{
  GLint location = get_uniform_location(varname);

  if (location >= 0) 
  {
#if UNVOX_GL_DIRECT_STATE_ACCESS
    glProgramUniform1f(id_, location, v0);
#else 
    glUniform1f(location, v0);
#endif
  } 
}


////////////////////////////////////////////////////////////////////////////////
void
program::set_uniform2f(char const* varname, GLfloat v0, GLfloat v1) const
{
  GLint location = get_uniform_location(varname);

  if (location >= 0) 
  {
#if UNVOX_GL_DIRECT_STATE_ACCESS
    glProgramUniform2f(id_, location, v0, v1);
#else 
    glUniform2f(location, v0, v1);
#endif
  }
}


////////////////////////////////////////////////////////////////////////////////
void
program::set_uniform3f(char const* varname, GLfloat v0, GLfloat v1, GLfloat v2) const
{
  GLint location = get_uniform_location(varname);

  if (location >= 0) 
  {
#if UNVOX_GL_DIRECT_STATE_ACCESS
    glProgramUniform3f(id_, location, v0, v1, v2);
#else 
    glUniform3f(location, v0, v1, v2);
#endif
  }
}


////////////////////////////////////////////////////////////////////////////////
void
program::set_uniform4f(char const* varname, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) const
{
  GLint location = get_uniform_location(varname);

  if (location >= 0) 
  {
#if UNVOX_GL_DIRECT_STATE_ACCESS
    glProgramUniform4f(id_, location, v0, v1, v2, v3);
#else 
    glUniform4f(location, v0, v1, v2, v3);
#endif
  } 

  //assert((location >= 0) && "set_uniform4f() : uniform not in use");
}


////////////////////////////////////////////////////////////////////////////////
void
program::set_uniform1i(char const* varname, GLint v0) const
{
  GLint location = get_uniform_location(varname);

  if (location >= 0) 
  {
#if UNVOX_GL_DIRECT_STATE_ACCESS
    glProgramUniform1i(id_, location, v0);
#else 
    glUniform1i(location, v0);
#endif
  } 
}


////////////////////////////////////////////////////////////////////////////////
void
program::set_uniform2i(char const* varname, GLint v0, GLint v1) const
{
  GLint location = get_uniform_location(varname);

  if (location >= 0) 
  {
#if UNVOX_GL_DIRECT_STATE_ACCESS
    glProgramUniform2i(id_, location, v0, v1);
#else 
    glUniform2i(location, v0, v1);
#endif
  } 
}


////////////////////////////////////////////////////////////////////////////////
void
program::set_uniform3i(char const* varname, GLint v0, GLint v1, GLint v2) const
{
  GLint location = get_uniform_location(varname);

  if (location >= 0) 
  {
#if UNVOX_GL_DIRECT_STATE_ACCESS
    glProgramUniform3i(id_, location, v0, v1, v2);
#else 
    glUniform3i(location, v0, v1, v2);
#endif
  } 
}


////////////////////////////////////////////////////////////////////////////////
void
program::set_uniform4i(char const* varname, GLint v0, GLint v1, GLint v2, GLint v3) const
{
  GLint location = get_uniform_location(varname);

  if (location >= 0) 
  {
#if UNVOX_GL_DIRECT_STATE_ACCESS
    glProgramUniform4i(id_, location, v0, v1, v2, v3);
#else 
    glUniform4i(location, v0, v1, v2, v3);
#endif
  } 
}


////////////////////////////////////////////////////////////////////////////////
void
program::set_uniform1fv(char const* varname, GLsizei count, GLfloat* value) const
{
  GLint location = get_uniform_location(varname);

  if (location >= 0) 
  {
#if UNVOX_GL_DIRECT_STATE_ACCESS
    glProgramUniform1fv(id_, location, count, value);
#else 
    glUniform1fv(location, count, value);
#endif
  } 
}


////////////////////////////////////////////////////////////////////////////////
void
program::set_uniform2fv(char const* varname, GLsizei count, GLfloat* value) const
{
  GLint location = get_uniform_location(varname);

  if (location >= 0) 
  {
#if UNVOX_GL_DIRECT_STATE_ACCESS
    glProgramUniform2fv(id_, location, count, value);
#else 
    glUniform2fv(location, count, value);
#endif
  } 
}


////////////////////////////////////////////////////////////////////////////////
void
program::set_uniform3fv(char const* varname, GLsizei count, GLfloat* value) const
{
  GLint location = get_uniform_location(varname);

  if (location >= 0) 
  {
#if UNVOX_GL_DIRECT_STATE_ACCESS
    glProgramUniform3fv(id_, location, count, value);
#else 
    glUniform3fv(location, count, value);
#endif
  }
}


////////////////////////////////////////////////////////////////////////////////
void
program::set_uniform4fv(char const* varname, GLsizei count, GLfloat* value) const
{
  GLint location = get_uniform_location(varname);

  if (location >= 0) 
  {
#if UNVOX_GL_DIRECT_STATE_ACCESS
    glProgramUniform4fv(id_, location, count, value);
#else 
    glUniform4fv(location, count, value);
#endif
  }
}


////////////////////////////////////////////////////////////////////////////////
void
program::set_uniform1iv(char const* varname, GLsizei count, GLint* value) const
{
  GLint location = get_uniform_location(varname);

  if (location >= 0) 
  {
#if UNVOX_GL_DIRECT_STATE_ACCESS
    glProgramUniform1iv(id_, location, count, value);
#else 
    glUniform1iv(location, count, value);
#endif
  }
}


////////////////////////////////////////////////////////////////////////////////
void
program::set_uniform2iv(char const* varname, GLsizei count, GLint* value) const
{
  GLint location = get_uniform_location(varname);

  if (location >= 0) 
  {
#if UNVOX_GL_DIRECT_STATE_ACCESS
    glProgramUniform2iv(id_, location, count, value);
#else 
    glUniform2iv(location, count, value);
#endif
  }
}


////////////////////////////////////////////////////////////////////////////////
void
program::set_uniform3iv(char const* varname, GLsizei count, GLint* value) const
{
  GLint location = get_uniform_location(varname);

  if (location >= 0) 
  {
#if UNVOX_GL_DIRECT_STATE_ACCESS
    glProgramUniform3iv(id_, location, count, value);
#else 
    glUniform3iv(location, count, value);
#endif
  }
}


////////////////////////////////////////////////////////////////////////////////
void
program::set_uniform4iv(char const* varname, GLsizei count, GLint* value) const
{
  GLint location = get_uniform_location(varname);

  if (location >= 0) 
  {
#if UNVOX_GL_DIRECT_STATE_ACCESS
    glProgramUniform4iv(id_, location, count, value);
#else 
    glUniform4iv(location, count, value);
#endif
  }
}


////////////////////////////////////////////////////////////////////////////////
void
program::set_uniform_matrix2fv(char const* varname, GLsizei count, GLboolean transpose, GLfloat* value) const
{
  GLint location = get_uniform_location(varname);

  if (location >= 0) 
  {
#if UNVOX_GL_DIRECT_STATE_ACCESS
    glProgramUniformMatrix2fv(id_, location, count, transpose, value);
#else 
    glUniformMatrix2fv(location, count, transpose, value);
#endif
  }
}


////////////////////////////////////////////////////////////////////////////////
void
program::set_uniform_matrix3fv(char const* varname, GLsizei count, GLboolean transpose, GLfloat* value) const
{
  GLint location = get_uniform_location(varname);

  if (location >= 0) 
  {
#if UNVOX_GL_DIRECT_STATE_ACCESS
    glProgramUniformMatrix3fv(id_, location, count, transpose, value);
#else 
    glUniformMatrix3fv(location, count, transpose, value);
#endif
  }
}


////////////////////////////////////////////////////////////////////////////////
void
program::set_uniform_matrix4fv(char const* varname, GLsizei count, GLboolean transpose, GLfloat const* value) const
{
  GLint location = get_uniform_location(varname);

  if (location >= 0) 
  {
#if UNVOX_GL_DIRECT_STATE_ACCESS
    glProgramUniformMatrix4fv(id_, location, count, transpose, value);
#else 
    glUniformMatrix4fv(location, count, transpose, value);
#endif
  }
}


////////////////////////////////////////////////////////////////////////////////
void        
program::set_uniform_matrix2x3fv( char const* varname, GLsizei count, GLboolean transpose, GLfloat* value ) const
{
  GLint location = get_uniform_location(varname);

  if (location >= 0) 
  {
#if UNVOX_GL_DIRECT_STATE_ACCESS
    glProgramUniformMatrix2x3fv(id_, location, count, transpose, value);
#else 
    glUniformMatrix2x3fv(location, count, transpose, value);
#endif
  }
}


////////////////////////////////////////////////////////////////////////////////
void        
program::set_uniform_matrix2x4fv( char const* varname, GLsizei count, GLboolean transpose, GLfloat* value ) const
{
  GLint location = get_uniform_location(varname);

  if (location >= 0) 
  {
#if UNVOX_GL_DIRECT_STATE_ACCESS
    glProgramUniformMatrix2x4fv(id_, location, count, transpose, value);
#else 
    glUniformMatrix2x4fv(location, count, transpose, value);
#endif
  }
}


////////////////////////////////////////////////////////////////////////////////
void        
program::set_uniform_matrix3x2fv( char const* varname, GLsizei count, GLboolean transpose, GLfloat* value ) const
{
  GLint location = get_uniform_location(varname);

  if (location >= 0) 
  {
#if UNVOX_GL_DIRECT_STATE_ACCESS
    glProgramUniformMatrix3x2fv(id_, location, count, transpose, value);
#else 
    glUniformMatrix3x2fv(location, count, transpose, value);
#endif
  }
}


////////////////////////////////////////////////////////////////////////////////
void        
program::set_uniform_matrix3x4fv( char const* varname, GLsizei count, GLboolean transpose, GLfloat* value ) const
{
  GLint location = get_uniform_location(varname);

  if (location >= 0) 
  {
#if UNVOX_GL_DIRECT_STATE_ACCESS
    glProgramUniformMatrix3x4fv(id_, location, count, transpose, value);
#else 
    glUniformMatrix3x4fv(location, count, transpose, value);
#endif
  }
}


////////////////////////////////////////////////////////////////////////////////
void        
program::set_uniform_matrix4x2fv( char const* varname, GLsizei count, GLboolean transpose, GLfloat* value ) const
{
  GLint location = get_uniform_location(varname);

  if (location >= 0) 
  {
#if UNVOX_GL_DIRECT_STATE_ACCESS
    glProgramUniformMatrix4x2fv(id_, location, count, transpose, value);
#else 
    glUniformMatrix4x2fv(location, count, transpose, value);
#endif
  }
}


////////////////////////////////////////////////////////////////////////////////
void        
program::set_uniform_matrix4x3fv( char const* varname, GLsizei count, GLboolean transpose, GLfloat* value ) const
{
  GLint location = get_uniform_location(varname);

  if (location >= 0) 
  {
#if UNVOX_GL_DIRECT_STATE_ACCESS
    glProgramUniformMatrix4x3fv(id_, location, count, transpose, value);
#else 
    glUniformMatrix4x3fv(location, count, transpose, value);
#endif
  }
}


////////////////////////////////////////////////////////////////////////////////
GLint
program::set_vertex_attrib(char const* varname) const
{
  assert(is_linked_);

  GLint index = glGetAttribLocation(id_, varname);
  glBindAttribLocation(id_, index, varname);

  return index;
}


////////////////////////////////////////////////////////////////////////////////
void 
program::set_texturebuffer(char const* varname, texturebuffer& t, GLint unit) const
{
  t.bind(unit);
  set_uniform1i(varname, unit);
}

////////////////////////////////////////////////////////////////////////////////
void        
program::set_shaderstoragebuffer(char const* varname, shaderstoragebuffer& ssbo, unsigned binding_point) const
{
  GLuint location = glGetProgramResourceIndex(id_, GL_SHADER_STORAGE_BLOCK, varname);

  if (location == GL_INVALID_INDEX) {
    std::cout << "program::set_shaderstoragebuffer(): " << varname << "not found in program.\n" << std::endl;
  }
  else {
    ssbo.bind_base(binding_point);
    glShaderStorageBlockBinding(id_, location, binding_point);
  }
}

////////////////////////////////////////////////////////////////////////////////
void program::set_uniformbuffer(char const* varname, uniformbuffer& ubo, unsigned binding_point) const
{

  GLuint location = get_uniform_blockindex(varname);

  if (location == GL_INVALID_INDEX) {
    std::cout << "program::set_uniformbuffer(): " << varname << "not found in program.\n" << std::endl;
  }
  else {
    ubo.bind_base(binding_point);
    glUniformBlockBinding(id_, location, binding_point);
  }
}

////////////////////////////////////////////////////////////////////////////////
void 
program::set_texture1d(char const* varname, texture1d& t, GLint unit) const
{
  t.bind(unit);
  set_uniform1i(varname, unit);
}



////////////////////////////////////////////////////////////////////////////////
void 
program::set_texture2d(char const* varname, texture2d& t, GLint unit) const
{
  t.bind(unit);
  set_uniform1i(varname, unit);
}


////////////////////////////////////////////////////////////////////////////////
void 
program::set_texture3d(char const* varname, texture3d& t, GLint unit) const
{
  t.bind(unit);
  set_uniform1i(varname, unit);
}


////////////////////////////////////////////////////////////////////////////////
void 
program::set_texturearray(char const* varname, texturearray& t, GLint unit) const
{
  t.bind(unit);
  set_uniform1i(varname, unit);
}


////////////////////////////////////////////////////////////////////////////////
void 
program::set_cubemap(char const* varname, cubemap& c, GLint unit) const
{
  c.bind(unit);
  set_uniform1i(varname, unit);
}


////////////////////////////////////////////////////////////////////////////////
void 
program::bind_attrib_location(char const* varname, GLuint index) const
{
  assert(!is_linked_ && "bind_attrib_location() : trying to set location of an already linked program");
  glBindAttribLocation(id_, index, varname);
}


////////////////////////////////////////////////////////////////////////////////
void 
program::bind_fragdata_location(char const* varname, GLuint index) const
{
  assert(!is_linked_ && "bind_fragdata_location() : trying to set location of an already linked program");
  glBindFragDataLocation(id_, index, varname);
}


////////////////////////////////////////////////////////////////////////////////
GLint               
program::get_attrib_location(char const* varname) const
{
  return glGetAttribLocation(id_, varname);
}


////////////////////////////////////////////////////////////////////////////////
GLint
program::get_uniform_location(char const* varname) const
{
  return glGetUniformLocation(id_, varname);
}


////////////////////////////////////////////////////////////////////////////////
GLint               
program::get_uniform_blockindex(char const* varname) const
{
  return glGetUniformBlockIndex(id_, varname);
}


////////////////////////////////////////////////////////////////////////////////
GLint               
program::get_uniform_blocksize(char const* varname) const
{
  GLint blocksize;
  glGetActiveUniformBlockiv(id_, glGetUniformBlockIndex(id_, varname), GL_UNIFORM_BLOCK_DATA_SIZE, &blocksize);
  return blocksize;
}

////////////////////////////////////////////////////////////////////////////////
GLint program::get_active_atomic_counters() const
{
  return get_parameter(GL_ACTIVE_ATOMIC_COUNTER_BUFFERS);
}

////////////////////////////////////////////////////////////////////////////////
GLint program::get_parameter(GLenum parameter_name) const
{
  GLint param;
  glGetProgramiv(id_, parameter_name, &param);
  return param;
}


////////////////////////////////////////////////////////////////////////////////
void                 
program::set_uniform_blockbinding(GLuint blockIndex, GLuint blockBinding ) const
{
  glUniformBlockBinding(id_, blockIndex, blockBinding);
}


////////////////////////////////////////////////////////////////////////////////
void                 
program::get_active_uniform_blockiv(GLuint uniformBlockIndex, GLenum pname, GLint *params) const
{
  glGetActiveUniformBlockiv(id_, uniformBlockIndex, pname, params);
}



} } // namespace unvox / namespace gl

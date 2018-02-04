#include "../../include/gl/shader.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

gl::shader::shader() {

}

void gl::shader::create() {
  std::cout<<"Empty parameters on gl::shader::create!\n";
}

void gl::shader::create(const std::string& data, GLenum type) {
  destroy();

  _name = glCreateShader(type);

  if(data.empty()) {
    std::cout<<"Warning: Data passed to shader is empty!\n";
  }
  
  source(data);

  compile();
}

void gl::shader::source(const std::string& src) {
  const GLint len = src.length();
  const char* dat = &src[0];

  glShaderSource(_name, 1, &dat, &len);
}

bool gl::shader::compile() {
  glCompileShader(_name);
  
  GLint info = 0;
  glGetShaderiv(_name, GL_COMPILE_STATUS, &info);

  if(info) {
    return true;
  }

  std::cout<<"Shader compilation failed!\n";

  glGetShaderiv(_name, GL_INFO_LOG_LENGTH, &info);

  char* log = (char*)operator new(info);

  glGetShaderInfoLog(_name, info, NULL, log);

  std::cout<<log<<"\n";

  delete log;

  return false;
}

bool gl::shader::load(const std::string& file, GLenum type) {
  std::ifstream fi(file);

  if(!fi.is_open()) {
    std::cout<<"Failed to load shader '"<<file<<"'!\n";
    return false;
  }

  std::stringstream buff;
  buff << fi.rdbuf();

  create(buff.str(), type);

  fi.close();
  
  return true;
}

void gl::shader::destroy() {
  if(!_name) return;

  glDeleteShader(_name);
}

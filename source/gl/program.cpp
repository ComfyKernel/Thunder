#include "../../include/gl/program.hpp"

#include <iostream>

gl::program::program() {

}

void gl::program::create() {
  destroy();

  _name = glCreateProgram();
}

void gl::program::create(const std::initializer_list<shader>& shaders) {
  create();

  for(const auto& i : shaders) {
    attach(i);
  }

  link();
}

void gl::program::attach(const shader& shad) {
  glAttachShader(_name, shad);
}

bool gl::program::link() {
  glLinkProgram(_name);

  GLint info = 0;

  glGetProgramiv(_name, GL_LINK_STATUS, &info);

  if(info) return true;

  std::cout<<"Program link failed!\n";

  glGetProgramiv(_name, GL_INFO_LOG_LENGTH, &info);

  char* log = (char*)operator new(info);

  glGetProgramInfoLog(_name, info, NULL, log);

  std::cout<<log<<"\n";

  delete log;
}

void gl::program::destroy() {
  if(!_name) return;

  glDeleteProgram(_name);
}

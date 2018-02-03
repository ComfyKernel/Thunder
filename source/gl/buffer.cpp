#include "../../include/gl/buffer.hpp"

#include <iostream>

gl::buffer::buffer() { }

void gl::buffer::create() {
  destroy();

  glGenBuffers(1, &_name);
}

void gl::buffer::create(void* data, size_t len,
			GLenum type, GLenum draw) {
  create();

  glBindBuffer(type, _name);
  glBufferData(type, len, data, draw);
}

void gl::buffer::destroy() {
  if(!_name) return;

  glDeleteBuffers(1, &_name);
}

#include "../../include/gl/framebuffer.hpp"

gl::framebuffer::framebuffer () {
  _name = 0;
}

const GLuint& gl::framebuffer::texture() {
  return _texBuff;
}

void gl::framebuffer::create () {
  destroy();

  glGenFramebuffers(1, &_name);
}

void gl::framebuffer::create (const uint2d& size) {
  destroy();

  _texBuffered = true;
  
  glGenTextures(1, &_texBuff);
  glBindTexture(GL_TEXTURE_2D, _texBuff);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  
  glGenFramebuffers(1, &_name);
  bind();
  
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texBuff, 0);
}

void gl::framebuffer::destroy() {
  if(!_name) return;

  if(_texBuffered && _texBuff) {
    glDeleteTextures(1, &_texBuff);
    _texBuff = 0;
  }
  
  glDeleteFramebuffers(1, &_name);
  _texBuff = 0;
}

void gl::framebuffer::bind() {
  glBindFramebuffer(GL_FRAMEBUFFER, _name);
}

void gl::framebuffer::clear() {
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

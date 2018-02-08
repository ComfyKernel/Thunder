#include "../../include/gl/texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../../stb/stb_image.h"

#include <iostream>

const int2d& gl::texture::size() { return _size; }

gl::texture::texture() { }

void gl::texture::create() {
  destroy();

  glGenTextures(1, &_name);
}

bool gl::texture::load(const std::string& file) {
  create();
  
  int w, h, d;

  unsigned char* data = stbi_load(file.c_str(), &w, &h, &d, STBI_rgb_alpha);

  if(data == NULL) {
    std::cout<<"Failed to load image '"<<file<<"'\n";
    
    return false;
  }

  _size.x = w;
  _size.y = h;
  
  glBindTexture(GL_TEXTURE_2D, _name);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,
	       w, h, 0, GL_RGBA,
	       GL_UNSIGNED_BYTE, data);

  stbi_image_free(data);

  return true;
}

void gl::texture::destroy() {
  if(!_name) return;

  glDeleteTextures(1, &_name);

  _name = 0;
}

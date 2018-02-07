#include "../../include/gl/texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../../stb/stb_image.h"

#include <iostream>

gl::texture::texture() { }

void gl::texture::create() {
  destroy();

  glGenTextures(1, &_name);
}

bool gl::texture::load(const std::string& file) {
  int w, h, d;

  unsigned char* data = stbi_load(file.c_str(), &w, &h, &d, STBI_rgb_alpha);

  if(data == NULL) {
    std::cout<<"Failed to load image '"<<file<<"'\n";
    
    return false;
  }
  
  glBindTexture(GL_TEXTURE_2D, _name);

  stb_image_free(data);

  return true;
}

void gl::texture::destroy() {
  if(!_name) return;

  glDeleteTextures(1, &_name);

  _name = 0;
}

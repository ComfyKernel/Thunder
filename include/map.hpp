#ifndef H_MAP_HPP
#define H_MAP_HPP

#include <vector>
#include <string>

#include "gl/buffer.hpp"

struct layer {
public:
  unsigned short* data;

  float*        vertices;
  unsigned int* indices;
  float*        uvs;

  gl::buffer vbuff;
  gl::buffer ibuff;
  gl::buffer ubuff;
};

class map {
public:
  unsigned int width;
  unsigned int height;

  std::vector<layer> layers;

  map();
  map(const std::string&);

  bool load(const std::string&);
};

#endif

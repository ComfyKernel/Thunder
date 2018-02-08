#ifndef H_GL_TEXTURE_SINGLE_HPP
#define H_GL_TEXTURE_SINGLE_HPP

#include "common.hpp"
#include "../units/special.hpp"

#include <string>

namespace gl {
  class texture : public object {
  protected:
    int2d _size;
    
  public:
    const int2d& size();
    
    texture();

    void create();

    bool load  (const std::string&);

    void destroy();
  };
};

#endif

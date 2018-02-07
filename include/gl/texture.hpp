#ifndef H_GL_TEXTURE_SINGLE_HPP
#define H_GL_TEXTURE_SINGLE_HPP

#include "common.hpp"

namespace gl {
  class texture : public object {
  public:
    texture();

    void create();

    bool load  (const std::string&);

    void destroy();
  };
};

#endif

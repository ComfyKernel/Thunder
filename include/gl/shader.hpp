#ifndef H_GL_SHADER_SINGLE_HPP
#define H_GL_SHADER_SINGLE_HPP

#include "common.hpp"

#include <string>

namespace gl {
  class shader : public object {    
  public:
    shader();

    void create ();
    void create (const std::string&, GLenum);

    bool load   (const std::string&, GLenum);
    
    void destroy();
  };
};

#endif

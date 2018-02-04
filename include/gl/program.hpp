#ifndef H_GL_PROGRAM_HPP
#define H_GL_PROGRAM_HPP

#include "common.hpp"
#include "shader.hpp"

#include <initializer_list>

namespace gl {
  class program : public object {
  public:
    program();

    void create();
    void create(const std::initializer_list<shader>&);

    void attach(const shader&);
    bool link  ();

    void destroy();
  };
};

#endif

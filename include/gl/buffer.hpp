#ifndef H_GL_BUFFER_SINGLE_HPP
#define H_GL_BUFFER_SINGLE_HPP

#include "common.hpp"

namespace gl {
  class buffer : public object {
  public:
    buffer();

    void create ();
    void create (void*, size_t, GLenum, GLenum);
    
    void destroy();
  };
};

#endif

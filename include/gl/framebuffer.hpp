#ifndef H_GL_FRAMEBUFFER_SINGLE_HPP
#define H_GL_FRAMEBUFFER_SINGLE_HPP

#include "common.hpp"
#include "../units/special.hpp"

namespace gl {
  class framebuffer : public object {
  protected:
    bool   _texBuffered = false;
    GLuint _texBuff;
    
  public:
    framebuffer ();

    const GLuint& texture();

    void create ();
    void create (const uint2d&);
    void destroy();
    
    void bind   ();

    static void clear();
  };
};

#endif

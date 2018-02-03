#ifndef H_GL_COMMON_SINGLE_HPP
#define H_GL_COMMON_SINGLE_HPP

#include <GL/glew.h>

namespace gl {
  class object {
  protected:
    GLuint _name = 0;
  public:
    GLuint name() const;
    object();

    virtual void create () { };
    virtual void destroy() { };

    operator GLuint() const;
  };
};

#endif

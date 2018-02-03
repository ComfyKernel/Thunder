#ifndef H_GL_SHADER_SINGLE_HPP
#define H_GL_SHADER_SINGLE_HPP

namespace gl {
  class shader : public object {
  public:
    shader();

    void create ();
    void destroy();
  };
};

#endif

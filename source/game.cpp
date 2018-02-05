#include "../include/game.hpp"
#include "../include/window.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <exception>

#include <GL/glew.h>

void dbg_gl_message_callback(__attribute__((unused)) GLenum  src,
			     __attribute__((unused)) GLenum  type,
			                             GLuint  id,
			     __attribute__((unused)) GLenum  severity,
			     __attribute__((unused)) GLsizei length,
			                       const GLchar* message,
			     __attribute__((unused)) const void* userParam) {
  std::cout<<"[GL Info] [ID: "<<id<<"] "<<message<<"\n";
}

class th::game::_impl {
public:
  glm::mat4 __ortho;
  
  window win;

  bool running = false;

  gl::program __spr_prog;
  
  bool create(const std::string& name,
	      const uint2d& pos,
	      const uint2d& size) {
    if(!win.open(name, pos, size)) {
      throw std::runtime_error("Failed to create a window!\n");
      return false;
    }

    if(glewInit() != GLEW_OK) {
      win.close();
      
      throw std::runtime_error("Failed to initialize GLEW!\n");
      return false;
    }

    glEnable(GL_DEBUG_OUTPUT);

    glDebugMessageCallback(dbg_gl_message_callback, nullptr);

    running = true;

    return true;
  }

  void destroy() {
    running = false;
    
    win.close();
  }
};

static th::game* _curr_game;

th::game& th::game::currentGame() { return *_curr_game; }

glm::mat4&   th::game::getOrtho() {
  return _gimpl->__ortho;
}

gl::program& th::game::getSpriteShader() {
  return _gimpl->__spr_prog;
}

th::game::game()
  : _gimpl{new th::game::_impl()} {

}

bool th::game::run(const uint2d& pos, const uint2d& size) {
  _curr_game = this;
  
  if(!_gimpl->create(name(), pos, size)) {
    std::cout<<"Cannot run, window failed to create.\n";
    return false;
  }

  gl::shader spr_vshad;
  gl::shader spr_fshad;

  spr_vshad.load("sprite.vertex"  , GL_VERTEX_SHADER);
  spr_fshad.load("sprite.fragment", GL_FRAGMENT_SHADER);

  _gimpl->__spr_prog.create({spr_vshad, spr_fshad});

  const uint2d& w_size = _gimpl->win.size();
  
  _gimpl->__ortho = glm::ortho(0.f, (float)w_size.x, 0.f, (float)w_size.y, -0.1f, 100.f);

  onStart();

  while(_gimpl->running && _gimpl->win.isOpen()) {
    _gimpl->win.pollEvents();

    onUpdate(0.f);

    onDrawStart(0.f);
    onDraw     (0.f);
    onDrawEnd  (0.f);
    
    _gimpl->win.swap();
  }

  onExit();

  _gimpl->__spr_prog.destroy();

  _gimpl->destroy();
  
  return true;
}



th::game::~game() {
  delete _gimpl;
}

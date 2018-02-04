#include "../include/game.hpp"
#include "../include/window.hpp"

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
  window win;

  bool running = false;
  
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

th::game::game()
  : _gimpl{new th::game::_impl()} {

}

bool th::game::run(const uint2d& pos, const uint2d& size) {
  if(!_gimpl->create(name(), pos, size)) {
    std::cout<<"Cannot run, window failed to create.\n";
    return false;
  }

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

  _gimpl->destroy();
  
  return true;
}



th::game::~game() {
  delete _gimpl;
}

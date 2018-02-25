#include "../../include/window.hpp"
#include "../../include/game.hpp"

#include <SDL2/SDL.h>

#include <iostream>

bool _sdl_has_init_ = false;

class th::window::_impl {
public:
  SDL_Window* win;
  SDL_GLContext ctx;

  bool open=false;

  uint2d _siz, _pos;
  std::string _name;

  const uint2d& size() {
    int x, y;
    SDL_GetWindowSize(win, &x, &y);
    _siz.x = x; _siz.y = y;
    return _siz;
  }

  const uint2d& position() {
    int x, y;
    SDL_GetWindowPosition(win, &x, &y);
    _pos.x = x; _pos.y = y;
    return _pos;
  }

  unsigned int milliseconds() {
    return SDL_GetTicks();
  }
  
  bool create(const std::string& n, uint2d p, uint2d s) {
    _name = n;
    
    if(!_sdl_has_init_) {
      if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
	std::cout<<"Failed to initialize SDL2!\nReason :\n"
		 <<SDL_GetError()<<"\n";
	throw std::runtime_error(std::string("Failed to initialize SDL2!\n")
				 + SDL_GetError());
	return false;
      }
    }
    
    win = SDL_CreateWindow(n.c_str(),
			   p.x, p.y,
			   s.x, s.y,
			   SDL_WINDOW_OPENGL|
			   SDL_WINDOW_RESIZABLE);

    if(!win) {
      std::cout<<"Failed to create an SDL2 Window!\nReason :\n"
	       <<SDL_GetError()<<"\n";
      throw std::runtime_error(std::string("Failed to create an SDL2 Window!\n")
			       + SDL_GetError());
      return false;
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
			SDL_GL_CONTEXT_PROFILE_CORE );

    ctx = SDL_GL_CreateContext(win);
    SDL_GL_MakeCurrent(win, ctx);

    if(!ctx) {
      std::cout<<"Failed to get an OpenGL Context!\nReason :\n"
	       <<SDL_GetError()<<"\n";
      throw std::runtime_error(std::string("Failed get an OpenGL Contest!\n")
			       + SDL_GetError());
      return false;
    }

    open = true;

    return true;
  }

  void destroy() {
    open = false;
    
    SDL_DestroyWindow(win);
    SDL_GL_DeleteContext(ctx);
  }

  void poll(game* callback) {
    SDL_Event event;
    
    while(SDL_PollEvent(&event)) { 
      if(event.type == SDL_QUIT) {
	open = false;
      }

      if(callback != nullptr) {
	callback->onEventPoll(event);
      }
    }
  }

  void swap() {
    SDL_GL_SwapWindow(win);
  }
};

th::window::window()
  : _wimpl{new _impl()} {

}

th::window::window(const std::string& n,
		   uint2d p, uint2d s)
  : _wimpl{new _impl()} {
  open(n, p, s);
}

bool th::window::open(const std::string& n,
		      uint2d p, uint2d s) {
  return _wimpl->create(n, p, s);
}

void th::window::close() {
  _wimpl->destroy();
}

th::window::~window() {
  delete _wimpl;
}

bool th::window::isOpen() {
  return _wimpl->open;
}

void th::window::pollEvents(game* callback) {
  _wimpl->poll(callback);
}

void th::window::swap() {
  _wimpl->swap();
}

unsigned int th::window::milliseconds() const {
  _wimpl->milliseconds();
}

const std::string& th::window::name() const {
  _wimpl->_name;
}

const uint2d& th::window::size() const {
  _wimpl->size();
}

const uint2d& th::window::position() const {
  _wimpl->position();
}

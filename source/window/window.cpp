#include "../../include/window.hpp"

#include <SDL2/SDL.h>

#include <iostream>

bool _sdl_has_init_ = false;

class th::window::_impl {
public:
  SDL_Window* win;
  SDL_GLContext ctx;

  bool open=false;
  
  bool create(const std::string& n, uint2d p, uint2d s) {
    if(!_sdl_has_init_) {
      if(SDL_Init(SDL_INIT_VIDEO) != 0) {
	std::cout<<"Failed to initialized SDL2!\nReason :\n"
		 <<SDL_GetError()<<"\n";
	return false;
      }
    }
    
    win = SDL_CreateWindow(n.c_str(),
			   p.x, p.y,
			   s.x, s.y,
			   SDL_WINDOW_OPENGL|
			   SDL_WINDOW_RESIZABLE);

    if(!win) {
      std::cout<<"Failed to create an SDL2 window!\nReason :\n"
	       <<SDL_GetError()<<"\n";
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
      std::cout<<"Failed to get an OpenGL context!\nReason :\n"
	       <<SDL_GetError()<<"\n";
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

  void poll() {
    SDL_Event event;
    SDL_PollEvent(&event);

    if(event.type == SDL_QUIT) {
      open = false;
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

void th::window::pollEvents() {
  _wimpl->poll();
}

void th::window::swap() {
  _wimpl->swap();
}

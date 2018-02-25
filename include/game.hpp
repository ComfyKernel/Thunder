#ifndef H_GAME_SINGLE_HPP
#define H_GAME_SINGLE_HPP

#include "units/special.hpp"
#include "gl/program.hpp"
#include "window.hpp"

#include <string>

#include <glm/mat4x4.hpp>

extern "C" {
  namespace th {
    class game {
    protected:
      class _impl;
      _impl* _gimpl;

      float t_delta;
      float t_deltaEnd;
      float t_deltaStart;
    
    public:
      glm::mat4&   getOrtho();
      glm::mat4    camera;
      gl::program& getSpriteShader();
      
      static game& currentGame();

      float delta();
      float time ();

      window& win;
      
      game();

      bool run(const uint2d&, const uint2d&);

      virtual const std::string& name() const { }

      virtual void onStart () { };
      virtual void onExit  () { };

      virtual void onEventPoll(SDL_Event&) { }
    
      virtual void onUpdate   (float) { };

      virtual void onDrawStart(float) { };
      virtual void onDraw     (float) { };
      virtual void onDrawEnd  (float) { };

      virtual void onResize   () { };

      void quit();

      ~game();
    };
  };
}

#endif

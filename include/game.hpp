#ifndef H_GAME_SINGLE_HPP
#define H_GAME_SINGLE_HPP

#include "units/special.hpp"

#include <string>

extern "C" {
  namespace th {
    class game {
    protected:
      class _impl;
      _impl* _gimpl;
    
    public:
      game();

      bool run(const uint2d&, const uint2d&);

      virtual const std::string& name() const { }

      virtual void onStart () { };
      virtual void onExit  () { };
    
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

#ifndef H_WINDOW_SINGLE_HPP
#define H_WINDOW_SINGLE_HPP

#include "units/special.hpp"

#include <string>
extern "C" {
  namespace th {
    class window {
    private:
      class _impl;
      _impl* _wimpl;

      float t_delta;
      float t_deltaEnd;
      float t_deltaStart;
      
    public:
      window();
      window(const std::string&, uint2d, uint2d);

      float delta();
      float time ();
      
      bool open (const std::string&, uint2d, uint2d);
      void close();

      bool isOpen    ();
      void pollEvents();
      void swap      ();

      unsigned int       milliseconds() const;
      const std::string& name        () const;
      const uint2d&      position    () const;
      const uint2d&      size        () const;

      ~window();
    };
  };
}

#endif

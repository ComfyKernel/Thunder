#ifndef H_WINDOW_SINGLE_HPP
#define H_WINDOW_SINGLE_HPP

#include "units/special.hpp"

#include <string>

namespace th {
  class window {
  private:
    class _impl;
    _impl* _wimpl;
    
  public:
    window();
    window(const std::string&, uint2d, uint2d);

    bool open (const std::string&, uint2d, uint2d);
    void close();

    bool isOpen    ();
    void pollEvents();
    void swap      ();

    const std::string& name    () const;
    const uint2d&      position() const;
    const uint2d&      size    () const;

    ~window();
  };
};

#endif

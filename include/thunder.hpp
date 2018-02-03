#ifndef H_THUNDER_MAIN_HPP
#define H_THUNDER_MAIN_HPP

#include "units.hpp"
#include "window.hpp"
#include "game.hpp"
#include "gl.hpp"

#include <string>

extern "C" {
#define getArraySize(arr) (sizeof(arr)/sizeof(arr[0]))
  
  namespace th {
    const std::string& getProperty(const std::string&);
  };
};

#endif

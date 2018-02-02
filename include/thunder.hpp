#ifndef H_THUNDER_MAIN_HPP
#define H_THUNDER_MAIN_HPP

#include "units.hpp"
#include "window.hpp"
#include "game.hpp"

#include <string>

extern "C" {
  namespace th {
    const std::string& getProperty(const std::string&);
  };
};

#endif

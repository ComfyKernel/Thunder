#ifndef H_THUNDER_MAIN_HPP
#define H_THUNDER_MAIN_HPP

#include <string>

extern "C" {
  namespace th {
    const std::string& getProperty(const std::string&);
  };
};

#endif

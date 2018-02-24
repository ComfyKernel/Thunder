#include "inforeader.hpp"

#include <iostream>
#include <fstream>
#include <exception>

inforeader::inforeader() {

}

bool inforeader::open(const std::string& filename) {
  std::ifstream fi(filename);

  if(!fi.is_open()) {
    std::cout<<"[inforeader] Couldn't open file '"<<filename<<"'\n";
    
    return false;
  }

  return true;
}

void* inforeader::_getValue(const std::string& name) {
  for(size_t i=0; i < _element_names.size(); ++i) {
    if(_element_names[i] == name) {
      std::cout<<"Value found : '"<<name<<"'\n";
      return _element_values[i];
    }
  }

  std::cout<<"Value not found! '"<<name<<"'\n";

  throw std::runtime_error("[inforeader] Unable to return a NULL value (possible segfault)\n");
}

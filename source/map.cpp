#include "../include/map.hpp"

#include <fstream>
#include <iostream>
#include <iterator>

map::map() {

}

map::map(const std::string& file) {
  load(file);
}

bool map::load(const std::string& file) {
  std::ifstream fi(file, std::ios::in | std::ios::binary);

  std::cout<<"Loading map '"<<file<<"'\n";

  if(!fi.is_open()) {
    std::cout<<"Map not found!\n";
    return false;
  }
  
  fi.unsetf(std::ios::skipws);
  
  std::streampos fsize;

  fi.seekg(0, std::ios::end);
  fsize = fi.tellg();
  fi.seekg(0, std::ios::beg);

  std::vector<unsigned char> dat;
  dat.reserve(fsize);

  dat.insert(dat.begin(),
	     std::istream_iterator<unsigned char>(fi),
	     std::istream_iterator<unsigned char>());

  width  = ((dat[3] << 24) | (dat[2] << 16) | (dat[1] << 8) | dat[0]);
  height = ((dat[7] << 24) | (dat[6] << 16) | (dat[5] << 8) | dat[4]);

  std::cout<<"Map size : W: "<<width<<" H: "<<height<<"\n";

  layer l;

  
  
  layers.push_back(l);

  return true;
}

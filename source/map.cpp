#include "../include/map.hpp"

#include <fstream>
#include <iostream>
#include <iterator>
#include <cstring>

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

  auto getNum = [&](unsigned int p) -> uint32_t {
    return ((dat[p+3]<<24) | (dat[p+2]<<16) | (dat[p+1]<<8) | dat[p]);
  };

  width  = getNum(0);
  height = getNum(4);

  std::cout<<"Map size [Header] : W: "<<width<<" H: "<<height<<"\n";

  layer l;

  struct {
    uint32_t l_off;
    uint32_t l_size;
    
    uint32_t e_off;
    uint32_t e_size;
    
    uint32_t r_off;
    uint32_t r_size;
  } f_map;

  memcpy(&f_map.l_off, &dat[(dat.size()) - (6*sizeof(uint32_t))], 6*sizeof(uint32_t));

  std::cout<<"[Map Footer]\n"
	   <<"Layer offset : "<<f_map.l_off <<"\n"
	   <<"Layer size   : "<<f_map.l_size<<"\n"
	   <<"Entity offset : "<<f_map.e_off <<"\n"
	   <<"Entity size   : "<<f_map.e_size<<"\n"
	   <<"RoomTrigger offset : "<<f_map.r_off <<"\n"
	   <<"RoomTrigger size   : "<<f_map.r_size<<"\n"
	   <<"--------------------------\n";
  
  struct {
    uint32_t l_dat_off;
    uint32_t l_dat_size;

    uint32_t l_ver_off;
    uint32_t l_ver_size;
    
    uint32_t l_ind_off;
    uint32_t l_ind_size;
    
    uint32_t l_uvs_off;
    uint32_t l_uvs_size;
  } h_layer;

  memcpy(&h_layer.l_dat_off, &dat[f_map.l_off], 8*sizeof(uint32_t));

  std::cout<<"[Layer Header]\n"
	   <<"Data offset : "<<h_layer.l_dat_off <<"\n"
	   <<"Data size   : "<<h_layer.l_dat_size<<"\n"
	   <<"Vertex offset : "<<h_layer.l_ver_off <<"\n"
	   <<"Vertex size   : "<<h_layer.l_ver_size<<"\n"
	   <<"Indice offset : "<<h_layer.l_ind_off <<"\n"
	   <<"Indice size   : "<<h_layer.l_ind_size<<"\n"
	   <<"UV offset : "<<h_layer.l_uvs_off <<"\n"
	   <<"UV size   : "<<h_layer.l_uvs_size<<"\n"
	   <<"--------------------------\n";

  std::vector<float> vertices(h_layer.l_ver_size / sizeof(float));
  memcpy(&vertices[0], &dat[h_layer.l_ver_off + f_map.l_off], h_layer.l_ver_size);

  std::vector<uint32_t> indices(h_layer.l_ind_size / sizeof(uint32_t));
  memcpy(&indices[0], &dat[h_layer.l_ind_off + f_map.l_off], h_layer.l_ind_size);

  std::vector<float> uvs(h_layer.l_uvs_size / sizeof(float));
  memcpy(&uvs[0], &dat[h_layer.l_uvs_off + f_map.l_off], h_layer.l_uvs_size);

  std::cout<<"[Mesh Info]\n"
	   <<"Vertex size : "<<vertices.size()<<"\n"
	   <<"Index size  : "<<indices.size() <<"\n"
	   <<"UV size     : "<<uvs.size()     <<"\n"
	   <<"--------------------------\n";

  std::cout<<"Generating map buffers\n";
  
  l.vbuff.create(&vertices[0], vertices.size() * sizeof(float),
		 GL_ARRAY_BUFFER, GL_STATIC_DRAW);
  l.ibuff.create(&indices[0], indices.size() * sizeof(uint32_t),
		 GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
  l.ubuff.create(&uvs[0], uvs.size() * sizeof(float),
		 GL_ARRAY_BUFFER, GL_STATIC_DRAW);

  l.icount = indices.size();

  std::cout<<"Pushing layer\n";
  
  layers.push_back(l);

  return true;
}

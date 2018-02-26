#include "inforeader.hpp"
#include "map.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>

enum layertype {
  LT_PROP,
  LT_COLLISION,
  LT_LOGIC,
  LT_PATH,
  LT_NONE
};

typedef std::pair<std::string, layertype> _layerpair;

_layerpair _layerpairs[] = {
  _layerpair("_prop_"     , LT_PROP      ),
  _layerpair("_collision" , LT_COLLISION ),
  _layerpair("_logic"     , LT_LOGIC     ),
  _layerpair("_path_"     , LT_PATH      ),
  _layerpair("_none_"     , LT_NONE      )
};

struct layer {
public:
  std::string filename;

  layertype ltype;

  bool special;
  
  std::vector<uint16_t> data;

  std::vector<float>    m_vertices;
  std::vector<uint32_t> m_indices;
  std::vector<float>    m_uvs;

  void getBin(std::vector<char>& vec) {
    auto writeNum = [&](uint32_t n) {
      vec.push_back(*( (char*)(&n)));
      vec.push_back(*(((char*)(&n)) + 1));
      vec.push_back(*(((char*)(&n)) + 2));
      vec.push_back(*(((char*)(&n)) + 3));
    };

    writeNum((8 * 4));
    writeNum(data.size() * sizeof(uint16_t));
    
    writeNum((8 * 4) + (data.size() * sizeof(uint16_t)));
    writeNum(m_vertices.size() * sizeof(float));

    writeNum((8 * 4) + (data.size() * sizeof(uint16_t))
	     + (m_vertices.size() * sizeof(float)));
    writeNum(m_indices.size() * sizeof(uint32_t));

    writeNum((8 * 4) + (data.size() * sizeof(uint16_t))
	     + (m_vertices.size() * sizeof(float))
	     + (m_indices.size() * sizeof(uint32_t)));
    writeNum(m_uvs.size() * sizeof(float));

    for(unsigned int i = 0; i < data.size() * sizeof(uint16_t); ++i) {
      vec.push_back(*(((char*)(&data[0])) + i));
    }

    for(unsigned int i = 0; i < m_vertices.size() * sizeof(float); ++i) {
      vec.push_back(*(((char*)(&m_vertices[0])) + i));
    }

    for(unsigned int i = 0; i < m_indices.size() * sizeof(uint32_t); ++i) {
      vec.push_back(*(((char*)(&m_indices[0])) + i));
    }

    for(unsigned int i = 0; i < m_uvs.size() * sizeof(float); ++i) {
      vec.push_back(*(((char*)(&m_uvs[0])) + i));
    }
  }
};

struct entity {
public:
  uint32_t x;
  uint32_t y;

  uint32_t id;
  
  void getBin(std::vector<char>& vec) {
    auto writeNum = [&](uint32_t n) {
      vec.push_back(*( (char*)(&n)));
      vec.push_back(*(((char*)(&n)) + 1));
      vec.push_back(*(((char*)(&n)) + 2));
      vec.push_back(*(((char*)(&n)) + 3));
    };

    writeNum(x);
    writeNum(y);
    writeNum(id);
  }
};

struct roomtrigger {
public:
  uint32_t x;
  uint32_t y;

  uint32_t id;

  uint32_t nextroom;

  void getBin(std::vector<char>& vec) {
    auto writeNum = [&](uint32_t n) {
      vec.push_back(*( (char*)(&n)));
      vec.push_back(*(((char*)(&n)) + 1));
      vec.push_back(*(((char*)(&n)) + 2));
      vec.push_back(*(((char*)(&n)) + 3));
    };

    writeNum(x);
    writeNum(y);
    writeNum(id);
    writeNum(nextroom);
  }
};

struct map {
public:
  uint32_t width;
  uint32_t height;

  std::vector<layer>       layers;
  std::vector<entity>      entities;
  std::vector<roomtrigger> roomtriggers;

  void getBin(std::vector<char>& vec) {
    auto writeNum = [&](uint32_t n) {
      vec.push_back(*( (char*)(&n)));
      vec.push_back(*(((char*)(&n)) + 1));
      vec.push_back(*(((char*)(&n)) + 2));
      vec.push_back(*(((char*)(&n)) + 3));
    };

    writeNum(width);
    writeNum(height);
    
    uint32_t csize = vec.size();

    for(int i=layers.size() - 1; i>=0; --i) {
      if(!layers[i].special) {
	layers[i].getBin(vec);
      }
    }
    
    uint32_t nsize = vec.size();

    uint32_t l_off  = 8;
    uint32_t l_size = (nsize - csize);

    csize = vec.size();

    for(int i=0; i<entities.size(); ++i) {
      entities[i].getBin(vec);
    }

    nsize = vec.size();

    uint32_t e_off  = (l_off + l_size);
    uint32_t e_size = (nsize - csize);

    csize = vec.size();

    for(int i=0; i<roomtriggers.size(); ++i) {
      roomtriggers[i].getBin(vec);
    }

    nsize = vec.size();

    uint32_t r_off  = (e_off + e_size);
    uint32_t r_size = (nsize - csize);

    writeNum(l_off);
    writeNum(l_size);
    writeNum(e_off);
    writeNum(e_size);
    writeNum(r_off);
    writeNum(r_size);
  }
};

int main(int argc, char *argv[]) {
  std::cout<<"Starting CSV2Map\n";

  if(argc<3) {
    std::cout<<"No map file provided / No output file provided!\n";
    exit(-1);
  }

  std::cout<<"Loading MapInfo file '"<<argv[1]<<"'\n";

  uint32_t width  = 0;
  uint32_t height = 0;

  map m;
  
  inforeader ir;
  if(ir.open(argv[1])) {
    std::cout<<"Info reader open.\n";

    std::cout<<"Getting map size.\n";
    width  = ir.getValue<unsigned int>("width" );
    height = ir.getValue<unsigned int>("height");
    std::cout<<"Map size ( W: "<<width<<" H: "<<height<<" )\n";

    m.width  = width;
    m.height = height;

    std::cout<<"Getting layers.\n";
    for(const auto& i : ir.getValue<std::vector<std::string>>("layer")) {
      layer l;

      l.filename = i;

      for(const auto& v : _layerpairs) {
	if(l.filename.find(v.first) != std::string::npos) {
	  std::cout<<"Layer '"<<l.filename<<"' (type '"<<v.first<<"') Found!\n";
	  
	  l.ltype = v.second;
	  break;
	}
      }

      m.layers.push_back(l);
    }
  } else {
    std::cout<<"Failed to open info file '"<<argv[1]<<"'!\n";
    exit(1);
  }

  for(auto& l : m.layers) {
    std::ifstream lay(l.filename);

    if(lay.is_open()) {
      std::cout<<"Opening layer file '"<<l.filename<<"'\n";

      std::string num = "";
      
      std::vector<uint16_t> ldat;
      
      char c = '\0';
      while(lay.get(c)) {
        switch(c) {
	case '\n':
	case ',': {
	  long dat = std::stol(num, nullptr, 0);
	  
	  if(dat < 0) dat = 0;
	  
	  ldat.push_back(dat);
	  
	  num = "";
	  break;
	}
	default:
	  num += c;
	  break;
	}
      }

      switch(l.ltype) {
      case LT_PROP:
	l.data = ldat;

	std::cout<<"Generating mesh...\n";

	for(unsigned int x = 0; x < m.width; ++x) {
	  for(unsigned int y = 0; y < m.height; ++y) {
	    if(l.data[x + (((m.height - y) - 1) * m.width)] != 0) {
	      unsigned int index = l.m_vertices.size() / 2;

	      // Vertices //

	      l.m_vertices.push_back(x * 16);
	      l.m_vertices.push_back(y * 16);

	      l.m_vertices.push_back((x + 1) * 16);
	      l.m_vertices.push_back(y * 16);

	      l.m_vertices.push_back((x + 1) * 16);
	      l.m_vertices.push_back((y + 1) * 16);

	      l.m_vertices.push_back((x) * 16);
	      l.m_vertices.push_back((y + 1) * 16);

	      // Indices //
	      
	      l.m_indices.push_back(index);
	      l.m_indices.push_back(index + 1);
	      l.m_indices.push_back(index + 2);

	      l.m_indices.push_back(index + 2);
	      l.m_indices.push_back(index + 3);
	      l.m_indices.push_back(index);

	      // UVs //

	      unsigned int dat = l.data[x + (((m.height - y) - 1) * m.width)];

	      float uv_s = (1.f / 32.f);
	      float uv_x = uv_s * (dat % 32);
	      float uv_y = uv_s * (dat / 32);

	      l.m_uvs.push_back(uv_x);
	      l.m_uvs.push_back(uv_y + uv_s);
	      
	      l.m_uvs.push_back(uv_x + uv_s);
	      l.m_uvs.push_back(uv_y + uv_s);

	      l.m_uvs.push_back(uv_x + uv_s);
	      l.m_uvs.push_back(uv_y);
	      
	      l.m_uvs.push_back(uv_x);
	      l.m_uvs.push_back(uv_y);
	    }
	  }
	}
	break;
      case LT_LOGIC: {
	for(unsigned int i=0; i<ldat.size(); ++i) {
	  if(ldat[i] == 0) continue;

	  /*e.x = (i % m.width) * 16;
	  e.y = (i / m.width) * 16;
	  
	  e.id = 1024 - ldat[i];

	  std::cout<<"Adding entity '"<<e.id<<"' ( X: "<<e.x<<" Y: "<<e.y<<" )\n";
	  
	  m.entities.push_back(e);*/

	  unsigned int state = 0;
	  
	  switch(ldat[i]) {
	  case 1023:
	    state = 1;
	  case 1019:
	    entity e;

	    e.x = (i % m.width ) * 16;
	    e.y = (m.height - (i / m.height)) * 16;

	    if(state == 0) {
	      e.id = 0; // TODO //
	    } else {
	      e.id = 1;
	    }
	    
	    std::cout<<"Adding entity '"<<e.id<<"' ( X: "<<e.x<<" Y: "<<e.y<<" )\n";
	  
	    m.entities.push_back(e);
	    break;
	  case 1022:
	    roomtrigger rt;

	    rt.x = (i % m.width ) * 16;
	    rt.y = (m.height - (i / m.height)) * 16;

	    std::cout<<"Adding roomtrigger ( X: "<<rt.x<<" Y: "<<rt.y<<" )\n";

	    m.roomtriggers.push_back(rt);
	    break;
	  }
	}
	break;
      }
      default:
	std::cout<<"Unhandled layer type!\n";
	break;
      }

      std::cout<<"Layer size : "<<l.data.size()<<"\n";
    } else {
      std::cout<<"Failed to open layer file '"<<l.filename<<"'!\n";
      exit(2);
    }

    std::cout<<"Writing to file '"<<argv[2]<<"'\n";
    
    std::ofstream ofile(argv[2], std::ios::out | std::ofstream::binary);

    std::vector<char> binDat;
    m.getBin(binDat);

    ofile.write(&binDat[0], binDat.size());

    ofile.close();
    
    lay.close();
  }
}

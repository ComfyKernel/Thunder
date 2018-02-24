#include "inforeader.hpp"
#include "map.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>

enum layertype {
  LT_FOREGROUND,
  LT_BACKGROUND,
  LT_COLLISION,
  LT_LOGIC,
  LT_PATH,
  LT_NONE
};

typedef std::pair<std::string, layertype> _layerpair;

_layerpair _layerpairs[] = {
  _layerpair("_foreground", LT_FOREGROUND),
  _layerpair("_background", LT_BACKGROUND),
  _layerpair("_collision" , LT_COLLISION ),
  _layerpair("_logic"     , LT_LOGIC     ),
  _layerpair("_path_"     , LT_PATH      ),
  _layerpair("_none_"     , LT_NONE      )
};

struct layer {
public:
  std::string filename;

  layertype ltype;

  std::vector<unsigned short> data;
};

struct map {
public:
  unsigned int width;
  unsigned int height;

  std::vector<layer> layers;
};

int main(int argc, char *argv[]) {
  std::cout<<"Starting CSV2Map\n";

  if(argc<2) {
    std::cout<<"No map file provided!\n";
    exit(-1);
  }

  std::cout<<"Loading MapInfo file '"<<argv[1]<<"'\n";

  unsigned int width  = 0;
  unsigned int height = 0;

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
      
      char c = '\0';
      while(lay.get(c)) {
	switch(c) {
	case '\n':
	case ',': {
	  long dat = std::stol(num, nullptr, 0);
	  
	  if(dat < 0) dat = 0;
	  
	  l.data.push_back(dat);
	  
	  num = "";
	  break;
	}
	default:
	  num += c;
	  break;
	}
      }

      std::cout<<"Layer size : "<<l.data.size()<<"\n";
    } else {
      std::cout<<"Failed to open layer file '"<<l.filename<<"'!\n";
      exit(2);
    }

    lay.close();
  }
}

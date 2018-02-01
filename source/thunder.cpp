#include "../include/thunder.hpp"

#include <utility>
#include <vector>



#define _getArraySize(arr) (sizeof(arr)/sizeof(arr[0]))


typedef std::pair<std::string, std::string> __propPair;

std::vector<__propPair> __properties = {
  __propPair { "versionMajor", "0"     },
  __propPair { "versionMinor", "1"     },
  __propPair { "versionFlair", "Alpha" },
};

std::string __propNotFound = "[Property Not Found]";

const std::string& th::getProperty(const std::string& name) {
  for(const auto& p : __properties) {
    if(p.first == name) {
      return p.second;
    }
  }

  return __propNotFound;
}

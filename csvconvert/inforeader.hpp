#ifndef H_INFOREADER_HPP
#define H_INFOREADER_HPP

#include <string>
#include <vector>

class inforeader {
protected:
  std::vector<std::string> _element_names;
  std::vector<void*>       _element_values;
  
  void* _getValue(const std::string&);
public:
  inforeader();

  bool open(const std::string&);

  template<typename T>
  const T& getValue(const std::string& val) {
    return *((T*)_getValue(val));
  }
};

#endif

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

  std::string word;
  std::string type;
  std::string name;
  std::string value;
  while(fi >> word) {
    bool iscom_type = false;
    bool iscom_name = false;

    bool isval      = true;
    bool isstring   = false;
    
    std::string val = "";
    
    for(const auto& c : word) {
      if(!isstring) {
	switch(c) {
	case '(':
	  iscom_type = true;
	  isval      = false;
	  break;
	case ')':
	  if(iscom_type) {
	    type = val;

	    std::cout<<"[inforeader] Setting type to '"<<type<<"'\n";
	  }
	  break;
	case '[':
	  iscom_name = true;
	  isval      = false;
	  break;
	case ']':
	  if(iscom_name) {
	    name = val;
	  }
	  break;
	case '\'':
	  isstring = true;
	  break;
	default:
	  val += c;
	  break;
	}
      } else {
	switch(c) {
	case '\'':
	  isstring = false;
	  break;
	default:
	  val += c;
	  break;
	}
      }
    }

    if(isval) {
      value = val;
      
      std::cout<<"[inforeader] Found '"<<name<<
	"' of type '"<<type<<
	"' with value '"<<value<<"'\n";
      
      if(type == "uint") {
	unsigned int* val = new unsigned int(std::stoul(value, nullptr, 0));
	
	_element_names.push_back(name);
	_element_values.push_back(val);
      } else if(type == "list") {
	bool found = false;
	
	for(int i=0; i<_element_names.size(); ++i) {
	  if(_element_names[i] == name) {
	    found = true;

	    std::vector<std::string>* vec = (std::vector<std::string>*)_element_values[i];

	    vec->push_back(value);
	    
	    break;
	  }
	}

	if(!found) {
	  _element_names.push_back (name);
	  _element_values.push_back(new std::vector<std::string>);
	  ((std::vector<std::string>*)_element_values[_element_values.size() - 1])->push_back(value);
	}
      } else {
	std::cout<<"[inforeader] Unknown type for element '"<<name<<"' Defaulting to string\n";

	_element_names.push_back (name);
	_element_values.push_back(new std::string(val));
      }
    }
    
    if(iscom_type) {
      type = val;
    }
    
    if(iscom_name) {
      name = val;
    }
  }

  return true;
}

void* inforeader::_getValue(const std::string& name) {
  for(size_t i=0; i < _element_names.size(); ++i) {
    if(_element_names[i] == name) {
      std::cout<<"[inforeader] Value found : '"<<name<<"'\n";
      return _element_values[i];
    }
  }

  std::cout<<"[inforeader] Value not found! '"<<name<<"'\n";

  throw std::runtime_error("[inforeader] Unable to return a NULL value (possible segfault)\n");
}

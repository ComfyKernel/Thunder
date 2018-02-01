#include <iostream>
#include <exception>

#include <GL/glew.h>

#include "../include/thunder.hpp"

int main(int argc, char *argv[]) {
  std::cout<<"Thunder Version : "
	   <<"v"<<th::getProperty("versionMajor")
	   <<"."<<th::getProperty("versionMinor")
	   <<"-"<<th::getProperty("versionFlair")
	   <<"\n";

  th::window win;

  if(!win.open("Test Window [Thunder]",
	       uint2d(0, 0), uint2d(1280, 720))) {
    throw std::runtime_error("Failed to create a Thunder window.\n");
    return -1;
  }

  if(glewInit() != GLEW_OK) {
    std::cout<<"GLEW Failed to initialize!\n";
    return -1;
  }

  while(win.isOpen()) {
    win.pollEvents();

    glClear(GL_COLOR_BUFFER_BIT);
    win.swap();
  }
  
  return 0;
}

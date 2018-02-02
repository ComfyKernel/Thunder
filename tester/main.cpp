#include <iostream>
#include <exception>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "../include/thunder.hpp"

class testgame : public th::game {
private:
  const std::string _name = "Test Game";
  
public:
  const std::string& name() const { return _name; }

  void onStart() {
    std::cout<<"Starting\n";
  }

  void onExit() {
    std::cout<<"Exiting\n";
  }

  void onUpdate   (float delta) {
    
  }

  void onDrawStart(float delta) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

  void onDraw     (float delta) {

  }

  void onDrawEnd  (float delta) {

  }
};

int main(int argc, char *argv[]) {
  std::cout<<"Thunder Version : "
	   <<"v"<<th::getProperty("versionMajor")
	   <<"."<<th::getProperty("versionMinor")
	   <<"-"<<th::getProperty("versionFlair")
	   <<"\n";

  testgame game;

  try {
    game.run(uint2d(0, 0), uint2d(1280, 720));
  } catch(std::exception& e) {
    std::cout<<"A game error occurred (Is that how you spell it?)!\n";

    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
			     "Game Error [Thunder]",
			     e.what(),
			     NULL);
  }
  
  return 0;
}

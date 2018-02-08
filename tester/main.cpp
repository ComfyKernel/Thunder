#include <iostream>
#include <exception>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "../include/thunder.hpp"

class testgame : public th::game {
private:
  const std::string _name = "Test Game";

  rn::sprite spr1 = rn::sprite(float2d(0.f  , 0.f),
			       float2d(100.f, 100.f));

  rn::sprite spr2 = rn::sprite(float2d(0.f  , 0.f),
			       float2d(100.f, 100.f));

  rn::sprite spr3 = rn::sprite(float2d(0.f  , 0.f),
			       float2d(100.f, 100.f));

  GLuint vao;

  gl::texture tex1;
  gl::texture tex2;
  
public:
  const std::string& name() const { return _name; }

  void onStart() {
    std::cout<<"Starting\n";

    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glActiveTexture(GL_TEXTURE0);

    tex1.load("testimage.png");
    tex2.load("testimage2.png");

    spr1.setTexture(tex1);
    spr2.setTexture(tex1);
    spr3.setTexture(tex2);

    std::cout<<"Finished Startup\n";
  }

  void onExit() {
    std::cout<<"Exit called\n";

    glDeleteVertexArrays(1, &vao);
    
    std::cout<<"Exiting\n";
  }

  void onUpdate   (float delta) {
    spr3.position.x = (sin(time() / 1600.0f) * 200.f) + ((win.size().x / 2) - 50);
    spr3.position.y = (cos(time() / 1600.0f) * 200.f) + ((win.size().y / 2) - 50);
    
    spr2.position.x = (sin(time() / 800.0f) * 200.f) + ((win.size().x / 2) - 50);
    spr2.position.y = (cos(time() / 800.0f) * 200.f) + ((win.size().y / 2) - 50);

    spr1.position.x = (sin(time() / 400.f) * 200.f) + ((win.size().x / 2) - 50);
    spr1.position.y = (cos(time() / 400.f) * 200.f) + ((win.size().y / 2) - 50);
  }

  void onDrawStart(float delta) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

  void onDraw     (float delta) {
    spr1.draw ();
    spr2.draw();
    spr3.draw();

    rn::sprite::drawSprites();
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
    std::cout<<"A game error occurred (Is that how you spell it?)!\n"<<e.what()<<"\n";

    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
			     "Game Error [Thunder]",
			     e.what(),
			     NULL);
  }
  
  return 0;
}

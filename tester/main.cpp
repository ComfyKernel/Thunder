#include <iostream>
#include <exception>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <vector>

#include "../include/thunder.hpp"

class testgame : public th::game {
private:
  const std::string _name = "Test Game";

  rn::sprite floor = rn::sprite(int2d(0 , 0 ),
				int2d(128, 16));

  rn::sprite thing = rn::sprite(int2d(16, 20),
				int2d(16, 16));

  rn::sprite thing2 = rn::sprite(int2d(64, 20),
				 int2d(16, 16));
  
  rn::sprite scr   = rn::sprite(int2d(0   , 0  ),
				int2d(1280, 720));

  rectoid floor_col = rectoid(float2d(0.f, 0.f),
			      float2d(128.f, 16.f));
  rectoid thing_col = rectoid(float2d(16.f, 20.f),
			      float2d(16.f, 16.f));
  rectoid thing2_col = rectoid(float2d(64.f, 20.f),
			       float2d(16.f, 16.f));
  
  rn::mesh tmesh;

  gl::framebuffer tfbo;
  
  GLuint vao;

  gl::texture tex1;
  gl::texture tex2;

  map tmap;
  
public:
  const std::string& name() const { return _name; }

  void onStart() {
    std::cout<<"Starting\n";

    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glActiveTexture(GL_TEXTURE0);

    tex1.load("testimage.png");
    tex2.load("testimage2.png");

    floor.setTexture(tex1);
    thing.setTexture(tex2);
    thing2.setTexture(tex2);

    tfbo.create(uint2d(1280 / 4, 720 / 4));
    scr.setTexture(tfbo.texture());

    tmap.load("testmap/testmap.cmf");

    rectoidGravity(float2d(0.f, -0.1f));
    
    thing_col.frozen = false;
    thing_col.velocity = float2d(0.5f, 5.f);

    thing2_col.frozen = false;
    thing2_col.velocity = float2d(-0.5f, 5.f);
    
    std::cout<<"Finished Startup\n";
  }

  void onExit() {
    std::cout<<"Exit called\n";

    glDeleteVertexArrays(1, &vao);
    
    std::cout<<"Exiting\n";
  }

  void onUpdate   (float delta) {
    stepRectoid();

    thing.position  = int2d(thing_col.position.x, thing_col.position.y);
    thing2.position = int2d(thing2_col.position.x, thing2_col.position.y);
  }

  void onDrawStart(float delta) {
    
  }

  void onDraw     (float delta) {
    tfbo.bind();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    floor.draw();
    thing.draw();
    thing2.draw();

    rn::sprite::drawSprites();

    gl::framebuffer::clear();

    scr.draw();

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

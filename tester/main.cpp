#include <iostream>
#include <exception>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <vector>

#include "../include/thunder.hpp"

class testgame : public th::game {
private:
  const std::string _name = "Test Game";

  rn::sprite floor = rn::sprite(float2d(0.f  , 0.f ),
				float2d(300.f, 50.f));

  rn::sprite thing = rn::sprite(float2d(200.f, 200.f),
				float2d(50.f , 50.f));

  ph::boxcollider floor_col = ph::boxcollider(float2d(0.f  , 0.f ),
					      float2d(300.f, 50.f));

  ph::boxcollider thing_col = ph::boxcollider(float2d(200.f, 200.f),
					      float2d(50.f , 50.f ));

  rn::mesh tmesh;
  
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

    floor.setTexture(tex1);
    thing.setTexture(tex2);

    float3d vertices[] = {
      float3d(-1.0,-1.0, 0.0),
      float3d( 1.0,-1.0, 0.0),
      float3d( 0.0, 1.0, 0.0)
    };

    thing_col.frozen = false;
    
    ph::setGravity(float2d(0.f, -0.85f));
    
    std::cout<<"Finished Startup\n";
  }

  void onExit() {
    std::cout<<"Exit called\n";

    glDeleteVertexArrays(1, &vao);
    
    std::cout<<"Exiting\n";
  }

  void onUpdate   (float delta) {
    ph::stepPhysics();
    
    floor.position = floor_col.position;
    thing.position = thing_col.position;
  }

  void onDrawStart(float delta) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

  void onDraw     (float delta) {
    floor.draw();
    thing.draw();

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

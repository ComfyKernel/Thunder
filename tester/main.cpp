#include <iostream>
#include <exception>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "../include/thunder.hpp"

class testgame : public th::game {
private:
  const std::string _name = "Test Game";
  gl::buffer vbuff;
  gl::buffer ibuff;

  gl::shader vshad;
  gl::shader fshad;

  gl::program prog;

  GLuint vao;
  
public:
  const std::string& name() const { return _name; }

  void onStart() {
    std::cout<<"Starting\n";

    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);

    float fdat[] = {
      -1.f, -1.f, 0.f,
       1.f, -1.f, 0.f,
       0.f,  1.f, 0.f
    };
    
    vbuff.create(fdat, getArraySize(fdat), GL_ARRAY_BUFFER, GL_STATIC_DRAW);

    unsigned short idat[] = {
      0, 1, 2
    };

    ibuff.create(idat, getArraySize(idat), GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);

    fshad.load("test.vert", GL_VERTEX_SHADER);
    vshad.load("test.frag", GL_FRAGMENT_SHADER);

    prog.create({fshad, vshad});

    glUseProgram(prog);

    glEnableVertexAttribArray(0);

    std::cout<<"Finished Startup\n";
  }

  void onExit() {
    std::cout<<"Exit called\n";

    vbuff.destroy();
    ibuff.destroy();

    vshad.destroy();
    fshad.destroy();

    prog.destroy();

    glDeleteVertexArrays(1, &vao);
    
    std::cout<<"Exiting\n";
  }

  void onUpdate   (float delta) {
    
  }

  void onDrawStart(float delta) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

  void onDraw     (float delta) {
    glBindBuffer(GL_ARRAY_BUFFER, vbuff);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, (void*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibuff);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, (void*)0);
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

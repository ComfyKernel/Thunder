#include <iostream>
#include <exception>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <vector>

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../include/thunder.hpp"

class testgame : public th::game {
private:
  const std::string _name = "Test Game";

  rn::sprite thing2 = rn::sprite(int2d(16, 16),
				 int2d(16, 16));
  
  rn::sprite scr   = rn::sprite(int2d(0   , 0  ),
				int2d(1280, 720));

  rectoid thing2_col = rectoid(float2d(64.f, 20.f),
			       float2d(16.f, 16.f));
  
  rn::mesh tmesh;

  gl::framebuffer tfbo;
  
  GLuint vao;

  gl::texture tex1;
  gl::texture tex2;
  gl::texture mapset;

  map tmap;

  GLuint mp_tex;
  GLuint mp_mat;

  glm::mat4 mapmat;
  
public:
  uint2d campos = uint2d(0, 0);
  
  const std::string& name() const { return _name; }

  void onStart() {
    std::cout<<"Starting\n";

    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glActiveTexture(GL_TEXTURE0);

    tex1.load("testimage.png");
    tex2.load("testimage2.png");
    mapset.load("test-tileset.png");
    
    thing2.setTexture(tex2);

    tfbo.create(uint2d(1280 / 4, 720 / 4));
    scr.setTexture(tfbo.texture());
    scr.ignoreCamera = true;

    tmap.load("testmap/testmap.cmf");

    for(const auto& e : tmap.entities) {
      if(e.id == 1) {
	campos = uint2d(e.x, e.y);
	break;
      }
    }

    mp_tex = glGetUniformLocation(getSpriteShader(), "TEX");
    mp_mat = glGetUniformLocation(getSpriteShader(), "PVM");

    rectoidGravity(float2d(0.f, -0.1f));
    
    thing2_col.frozen   = false;
    thing2_col.position = float2d(campos.x, campos.y);
    thing2_col.velocity = float2d(0.f, 0.f);

    campos = uint2d(campos.x - ((1280 / 4) / 2), campos.y - ((720 / 4) / 2));

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    std::cout<<"Finished Startup\n";
  }

  void onExit() {
    std::cout<<"Exit called\n";

    glDeleteVertexArrays(1, &vao);
    
    std::cout<<"Exiting\n";
  }

  bool cm_up    = false;
  bool cm_down  = false;
  bool cm_right = false;
  bool cm_left  = false;

  void onUpdate   (float delta) {
    stepRectoid();

    thing2.position = int2d(thing2_col.position.x, thing2_col.position.y);

    if(cm_up) {
      campos.y += (200 * delta);
    }
    if(cm_down) {
      campos.y -= (200 * delta);
    }
    if(cm_left) {
      campos.x -= (200 * delta);
    }
    if(cm_right) {
      campos.x += (200 * delta);
    }
    
    camera = glm::translate(glm::mat4(1.f), glm::vec3(-(double)campos.x, -(double)campos.y, 0.0));
  }

  void onDrawStart(float delta) {
    
  }

  void onEventPoll(SDL_Event& event) {
    switch(event.type) {
    case SDL_KEYDOWN:
      switch(event.key.keysym.sym) {
      case SDLK_w:
	cm_up    = true;
	break;
      case SDLK_s:
	cm_down  = true;
	break;
      case SDLK_a:
	cm_left  = true;
	break;
      case SDLK_d:
	cm_right = true;
	break;
      }
      break;
    case SDL_KEYUP:
      switch(event.key.keysym.sym) {
      case SDLK_w:
	cm_up    = false;
	break;
      case SDLK_s:
	cm_down  = false;
	break;
      case SDLK_a:
	cm_left  = false;
	break;
      case SDLK_d:
	cm_right = false;
	break;
      }
      break;
    }
  }

  void onDraw     (float delta) {
    tfbo.bind();

    glClearColor(0, 0, 0, 1);
    glClear     (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    thing2.draw();

    rn::sprite::drawSprites();

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    mapmat = getOrtho() * camera;

    glActiveTexture(GL_TEXTURE0);
    glBindTexture  (GL_TEXTURE_2D, mapset);

    glUniform1i       (mp_tex, 0);
    glUniformMatrix4fv(mp_mat, 1, false, &mapmat[0][0]);
    
    for(unsigned int i=0; i<tmap.layers.size(); ++i) {
      glBindBuffer(GL_ARRAY_BUFFER, tmap.layers[i].vbuff);
      glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, (void*)0);
      
      glBindBuffer(GL_ARRAY_BUFFER, tmap.layers[i].ubuff);
      glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, (void*)0);
      
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tmap.layers[i].ibuff);
      glDrawElements(GL_TRIANGLES, tmap.layers[i].icount, GL_UNSIGNED_INT, (void*)0);
    }
    
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

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

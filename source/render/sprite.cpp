#include "../../include/render/sprite.hpp"
#include "../../include/game.hpp"

#include "../../include/gl/buffer.hpp"

#include <vector>
#include <iostream>

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

bool __sprite_draw_initialized = false;

gl::buffer __sprite_vertices;
gl::buffer __sprite_indices ;
gl::buffer __sprite_uvs     ;
  
std::vector<rn::sprite*> __draw_sprites;
  
unsigned int __add_sprite(rn::sprite* spr) {
  __draw_sprites.push_back(spr);
  return __draw_sprites.size() - 1;
}
  
void __del_sprite(unsigned int id) {
  __draw_sprites.erase(__draw_sprites.begin() + id);
    
  if(!__draw_sprites.size()) {
    std::cout<<"[SPRITE] No Sprites left! Deleting buffers\n";
      
    __sprite_vertices.destroy();
    __sprite_indices.destroy ();
  }
}
  
glm::mat4 __sprite_ortho;
glm::mat4 __sprite_out;
  
GLuint __spr_shad_matid,
       __spr_text_matid;
  
void __draw_active_sprites() {
  if(!__sprite_draw_initialized) {
    std::cout<<"[SPRITE] Creating sprite buffers\n";
      
    float verts[] =  {
      0.f, 0.f,
      1.f, 0.f,
      1.f, 1.f,
      0.f, 1.f
    };

    float uvs[] = {
      0.f, 0.f,
      1.f, 0.f,
      1.f, 1.f,
      0.f, 1.f
    };
      
    unsigned short indis[] = {
      0, 1, 2, 2, 3, 4
    };
      
    __sprite_vertices.create(verts, 8*sizeof(float         ),
			     GL_ARRAY_BUFFER        , GL_STATIC_DRAW);
    __sprite_indices.create (indis, 6*sizeof(unsigned short),
			     GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
    __sprite_uvs.create     (uvs  , 8*sizeof(float         ),
			     GL_ARRAY_BUFFER        , GL_STATIC_DRAW);
    
    __spr_shad_matid = glGetUniformLocation(th::game::currentGame().getSpriteShader(), "PVM");
    __spr_text_matid = glGetUniformLocation(th::game::currentGame().getSpriteShader(), "TEX");
      
    __sprite_draw_initialized = true;
  }
    
  glUseProgram(th::game::currentGame().getSpriteShader());
    
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
    
  glBindBuffer         (GL_ARRAY_BUFFER        , __sprite_vertices);
  glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, (void*)0);

  glBindBuffer         (GL_ARRAY_BUFFER        , __sprite_uvs);
  glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, (void*)0);
  
  glBindBuffer         (GL_ELEMENT_ARRAY_BUFFER, __sprite_indices );
    
  __sprite_ortho = th::game::currentGame().getOrtho();

  glActiveTexture(GL_TEXTURE0);
    
  for(auto& i : __draw_sprites) {
    if(i->__is_drawing) {
      i->__is_drawing = false;
      
      __sprite_out = __sprite_ortho;

      if(!i->ignoreCamera) {
	__sprite_out *= th::game::currentGame().camera;
      }
      
      __sprite_out *= glm::translate(glm::mat4(1),
				     glm::vec3(i->position.x, i->position.y, 0.f));
      __sprite_out *= glm::scale(glm::mat4(1),
				 glm::vec3(i->size.x, i->size.y, 0.f));
      
      glBindTexture(GL_TEXTURE_2D, i->__texture);
      
      if(i->textureIndependent) {
	
      }
      
      glUniformMatrix4fv(__spr_shad_matid, 1, false, &__sprite_out[0][0]);
      glUniform1i       (__spr_text_matid, 0);
      
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (void*)0);
    }
  }
}

void rn::sprite::drawSprites() {
  __draw_active_sprites();
}

GLuint rn::sprite::texture() { return __texture; }

void rn::sprite::setTexture(GLuint tex) {
  __texture = tex;
}

rn::sprite::sprite() { }
rn::sprite::sprite(const int2d& p, const int2d& s) {
  __id = __add_sprite(this);
  
  create(p, s);
}

rn::sprite::sprite(const int2d&  p, const int2d&  s,
		   const int2d& pt, const int2d& st) {
  __id = __add_sprite(this);
  
  create(p, s, pt, st);
}

void rn::sprite::create(const int2d& p, const int2d& s) {
  textureIndependent = false;
  
  position = p;
  size     = s;
}

void rn::sprite::create(const int2d&  p, const int2d&  s,
			const int2d& pt, const int2d& st) {
  textureIndependent = true;

  position = p;
  size     = s;

  texposition = pt;
  texsize     = st;
}

void rn::sprite::draw() {
  __is_drawing = true;
}

rn::sprite::~sprite() {
  __del_sprite(__id);
}

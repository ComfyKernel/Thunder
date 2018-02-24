#ifndef H_RENDER_SPRITE_HPP
#define H_RENDER_SPRITE_HPP

#include "../units/special.hpp"

#include "../gl/texture.hpp"

namespace rn {
  class sprite {
  protected:    
    unsigned int __id;

  public:
    GLuint __texture;
    bool   __is_drawing = false;
    
    static void drawSprites();

    int2d position;
    int2d size;
    
    int2d texposition;
    int2d texsize;

    GLuint texture();

    void setTexture(GLuint);

    bool textureIndependent = false;

    sprite();
    sprite(const int2d& pos   , const int2d& size);
    sprite(const int2d& pos   , const int2d& size,
	   const int2d& texpos, const int2d& texsize);
    
    void create(const int2d&, const int2d&);
    void create(const int2d&, const int2d&,
		const int2d&, const int2d&);
    
    void draw();

    ~sprite();
  };
};

#endif

#ifndef H_RENDER_SPRITE_HPP
#define H_RENDER_SPRITE_HPP

#include "../units/special.hpp"

#include "../gl/texture.hpp"

namespace rn {
  class sprite {
  protected:    
    unsigned int __id;

  public:
    const gl::texture* __texture;
    bool               __is_drawing = false;
    
    static void drawSprites();

    float2d position;
    float2d size;
    
    float2d texposition;
    float2d texsize;

    const gl::texture& texture();

    void setTexture(const gl::texture&);

    bool textureIndependent = false;

    sprite();
    sprite(const float2d& pos   , const float2d& size);
    sprite(const float2d& pos   , const float2d& size,
	   const float2d& texpos, const float2d& texsize);

    void create(const float2d&, const float2d&);
    void create(const float2d&, const float2d&,
		const float2d&, const float2d&);
    
    void draw();

    ~sprite();
  };
};

#endif

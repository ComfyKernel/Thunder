#ifndef H_RENDER_SPRITE_HPP
#define H_RENDER_SPRITE_HPP

#include "../units/special.hpp"

namespace rn {
  class sprite {
  public:
    unsigned int __id;
    bool         __is_drawing = false;

    static void drawSprites();

    float2d position;
    float2d size;
    
    float2d texposition;
    float2d texsize;

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

#ifndef H_RECTOID_HPP
#define H_RECTOID_HPP

#include "units/special.hpp"

class rectoid {
public:
  float2d position;
  float2d size;
  float2d velocity;

  bool frozen       = true;
  bool bounce       = false;
  bool colliding    = false;
  bool ignoreActive = false;

  float2d coldst;
  
  rectoid();
  rectoid(const float2d&, const float2d&);

  bool isColliding (const rectoid*) const;
  bool isHorizontal(const rectoid*) const;
  bool isVertical  (const rectoid*) const;
};

void stepRectoid();
void rectoidGravity(const float2d&);

#endif

#ifndef H_COLLIDER_SINGLE_HPP
#define H_COLLIDER_SINGLE_HPP

#include "../units/special.hpp"

namespace ph {
  void stepPhysics();
  void setGravity (float);
  
  class collider {
  protected:

  public:
    float2d velocity;
    float2d position;

    bool static=false;

    virtual bool isColliding() = 0;
  }
};

#endif

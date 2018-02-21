#ifndef H_COLLIDER_SINGLE_HPP
#define H_COLLIDER_SINGLE_HPP

#include "../units/special.hpp"

namespace ph {
  void stepPhysics();
  
  class collider {
  protected:

  public:
    float3d velocity;
    float3d position;

    virtual bool isColliding() = 0;
  }
};

#endif

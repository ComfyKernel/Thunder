#ifndef H_BOX_COLLIDER_SINGLE_HPP
#define H_BOX_COLLIDER_SINGLE_HPP

namespace ph {
  class boxcollider : public collider {
  protected:

  public:
    float2d size;
    
    bool isColliding();
  }
}

#endif

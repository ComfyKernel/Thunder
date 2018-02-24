#include "../include/rectoid.hpp"

#include <vector>
#include <cmath>

std::vector<rectoid*> rectoids;

float2d gravity;

void stepRectoid() {
  for(const auto& i : rectoids) {
    i->velocity += gravity;
    
    for(const auto& c : rectoids) {
      if(i == c) continue;

      if(i->isColliding(c)) {
	if(c->isHorizontal(i)) {
	  if(!i->frozen) {
	    if(i->bounce && abs(i->velocity.y) > 2.f) {
	      // i->velocity.y = -i->velocity.y / 1.5;
	    } else {
	      i->velocity.y = 0;
	    }
	    if(i->position.y > c->position.y) {
	      i->position.y = c->position.y + c->size.y - 1.f;
	    } else {
	      i->position.y = c->position.y - i->size.y;
	    }
	    i->velocity.x /= 1.15;
	  }
	} else if(c->isVertical(i)) {
	  i->velocity.x = 0;
	}
      }
    }

    if(!i->frozen) {
      i->position += i->velocity;
    }
  }
}

void rectoidGravity(const float2d& grav) {
  gravity = grav;
}

rectoid::rectoid() {
  rectoids.push_back(this);
}

rectoid::rectoid(const float2d& pos, const float2d& siz) {
  rectoids.push_back(this);
  
  position = pos;
  size     = siz;
}

bool rectoid::isColliding(const rectoid* rect) const {
  return (position.x < rect->position.x + rect->size.x && position.x + size.x > rect->position.x &&
	  position.y < rect->position.y + rect->size.y && position.y + size.y > rect->position.y);
}

bool rectoid::isHorizontal(const rectoid* rect) const {
  return (position.x < rect->position.x + rect->size.x && position.x + size.x > rect->position.x);
}

bool rectoid::isVertical(const rectoid* rect) const {
  return (position.y < rect->position.y + rect->size.y && position.y + size.y > rect->position.y);
}

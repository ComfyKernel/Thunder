#include "../include/rectoid.hpp"

#include <vector>
#include <cmath>
#include <iostream>

std::vector<rectoid*> rectoids;

float2d gravity;

void stepRectoid() {
  unsigned int count = 0;
  
  for(const auto& i : rectoids) {
    count++;

    if(!i->frozen)
      i->velocity += gravity;
    
    for(const auto& c : rectoids) {
      if(c == i) continue;

      if(i->isColliding(c)) {
	if(c->isHorizontal(i)) {
	  if(!i->frozen) {
	    if(i->bounce && abs(i->velocity.y) > 2.f) {
	      i->velocity.y = -i->velocity.y / 1.5;
	    } else {
	      i->velocity.y = 0;
	    }
	    i->velocity.x /= 1.15;

	    if(i->position.y < c->position.y + c->size.y) {
	      int dst = ((c->position.y + c->size.y) - i->position.y);
	      if(abs(dst) > 1) {
		i->position.y += dst;
	      }
	    }
	  }
	} else if(c->isVertical(i)) {
	  if(!i->frozen) {
	    if(i->bounce && abs(i->velocity.x) > 2.f) {
	      i->velocity.x = -i->velocity.x / 1.5;
	    } else {
	      i->velocity.x = 0;
	    }

	    if(i->position.x + i->size.x > c->position.x &&
	       !i->position.x > c->position.x) {
	      i->position.x -= ((i->position.x + i->size.x) - c->position.x);
	    }
	  }
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
  return (rect->position.x + (rect->size.x / 2) > position.x &&
	  rect->position.x + (rect->size.x / 2) < position.x + size.x);
}

bool rectoid::isVertical(const rectoid* rect) const {
  return (rect->position.y + (rect->size.y / 2) > position.y &&
	  rect->position.y + (rect->size.y / 2) < position.y + size.y);
}

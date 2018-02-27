#include "../include/rectoid.hpp"

#include <vector>
#include <cmath>
#include <iostream>

std::vector<rectoid*> rectoids;

float2d gravity;

float drag = 1.15f;

void stepRectoid() {
  unsigned int count = 0;
  
  for(const auto& i : rectoids) {
    count++;

    for(const auto& c : rectoids) {
      if(c == i) continue;

      if(i->ignoreActive && !c->frozen) {
	continue;
      }
      
      if(i->isColliding(c)) {
	i->colliding = true;

	float dstx = 0.f;
	float dsty = 0.f;
	
	if(i->position.y > c->position.y) {
	  dsty = abs(i->position.y - (c->position.y + c->size.y));
	} else {
	  dsty = abs(i->position.y - c->position.y);
	}

	if(i->position.x > c->position.x) {
	  dstx = abs(i->position.x - (c->position.x + c->size.x));
	} else {
	  dstx = abs(i->position.x - c->position.x);
	}
	
	i->coldst = float2d(dstx, dsty);
	break;
      } else {
	i->colliding = false;
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

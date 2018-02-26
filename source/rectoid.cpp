#include "../include/rectoid.hpp"

#include <vector>
#include <cmath>
#include <iostream>

std::vector<rectoid*> rectoids;

float2d gravity;

void stepRectoid() {
  unsigned int count = 0;

  for(unsigned int i=0; i < rectoids.size(); ++i) {
    count++;

    if(!rectoids[i]->frozen) {
      rectoids[i]->velocity +=gravity;
    }

    for(unsigned int c=0; c < rectoids.size(); ++c) {
      if(c == i) continue;

      if(rectoids[i]->isColliding(rectoids[c])) {
	rectoids[i]->velocity.x = 0;
	rectoids[i]->velocity.y = 0;
      }
    }

    if(!rectoids[i]->frozen) {
      rectoids[i]->position += rectoids[i]->velocity;
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

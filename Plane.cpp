#include <cmath>

#include "Plane.hpp"

//#define DEBUG_PLANE

#ifdef DEBUG_PLANE
#include <iostream>
#endif

Triple Plane::point() {
        return this->pos + Triple(this->pp.x * cos(this->ang) - this->pp.y * sin(this->ang),
                                  this->pp.x * sin(this->ang) + this->pp.y * cos(this->ang),
                                  this->pp.z);
}

Triple Plane::normal() {
        return Triple(this->n.x * cos(this->ang) - this->n.y * sin(this->ang),
                      this->n.x * sin(this->ang) + this->n.y * cos(this->ang),
                      this->n.z);
}

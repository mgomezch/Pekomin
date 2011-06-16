#include "Flee.hpp"
#include "Mobile.hpp"

#define DEBUG_FLEE

#ifdef DEBUG_FLEE
#include <iostream>
#endif

Flee::Flee(Mobile *character, Mobile *target, double maxSpeed, double fleeRadius) {
        this->character  = character ;
        this->target     = target    ;
        this->maxSpeed   = maxSpeed  ;
        this->fleeRadius = fleeRadius;
        this->dead       = false     ;
}

pair<bool, Triple> Flee::getVel(unsigned int ticks) {
        pair<bool, Triple> steering;

//      steering.second = character->pos - target->pos;
//      if (steering.second.length() < fleeRadius) {
//              steering.first = true;
//              steering.second.normalize();
//              steering.second *= maxSpeed;
//      }
//      return steering;

#ifdef DEBUG_FLEE
        cout << "Flee " << reinterpret_cast<int>(this) << ": dist == " << dist(character, target) << endl;
#endif
        steering.first = true;
        if (dist(character, target) < fleeRadius) {
                steering.second = (character->pos - target->pos).normalized() * maxSpeed;
        }
        return steering;
}

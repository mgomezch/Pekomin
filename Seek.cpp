#include "Seek.hpp"
#include "Mobile.hpp"

#define DEBUG_SEEK

#ifdef DEBUG_SEEK
#include <iostream>
#endif

Seek::Seek(Mobile *character, Mobile *target, double maxSpeed) {
        this->character = character;
        this->target    = target   ;
        this->maxSpeed  = maxSpeed ;
        this->dead      = false    ; 
}

pair<bool, Triple> Seek::getVel(unsigned int ticks) {
        pair<bool, Triple> steering;

//        steering.first = true;
//        steering.second = target->pos - character->pos;
//        steering.second.normalize();
//        steering.second *= maxSpeed;

#ifdef DEBUG_SEEK
        cout << "Seek " << reinterpret_cast<int>(this) << ": dist == " << dist(character, target) << endl;
#endif

        steering.first = true;
        steering.second = (character->pos - target->pos).normalized() * maxSpeed;

        return steering;
}

#include "Seek.hpp"
#include "Mobile.hpp"

Seek::Seek(Mobile *character, Mobile *target, double maxSpeed) {
        this->character = character;
        this->target    = target   ;
        this->maxSpeed  = maxSpeed ;
        this->dead      = false    ; 
}

pair<bool, Triple> Seek::getVel(unsigned int ticks) {
        pair<bool, Triple> steering;
        Triple cp, tp;

        steering.first = true;
        tie(cp, tp) = points(this->character, this->target);
        steering.second = tp - cp;
        steering.second.normalize();
        steering.second *= maxSpeed;

        return steering;
}

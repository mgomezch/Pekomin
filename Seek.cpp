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

        steering.first = true;
        steering.second = target->pos - character->pos;
        steering.second.normalize();
        steering.second *= maxSpeed;

        return steering;
}

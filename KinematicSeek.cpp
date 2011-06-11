#include "KinematicSeek.hpp"
#include "Ent.hpp"

KinematicSeek::KinematicSeek(Ent *character, Ent *target, double maxSpeed) {
        this->character = character;
        this->target    = target   ;
        this->maxSpeed  = maxSpeed ;
}

pair<bool, Triple> KinematicSeek::getVel(unsigned int ticks) {
        pair<bool, Triple> steering;
        steering.first = true;
        steering.second = target->pos - character->pos;
        steering.second.normalize();
        steering.second *= maxSpeed;
        //steering.second = getNewOrientation(character->ang, steering.second);

        return steering;
}

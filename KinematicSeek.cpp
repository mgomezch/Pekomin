#include "KinematicSeek.hpp"
#include "Ent.hpp"

KinematicSeek::KinematicSeek(Ent *character, Ent *target, double maxSpeed) {
        this->character = character;
        this->target    = target   ;
        this->maxSpeed  = maxSpeed ;
        this->dead      = false    ;
}

pair<bool, Triple> KinematicSeek::getVelIncr(unsigned int ticks) {
        pair<bool, Triple> steering;
        Triple cp, tp;

        steering.first = true;
        tie(cp, tp) = points(this->character, this->target);
        steering.second = tp - cp;
        steering.second.normalize();
        steering.second *= maxSpeed;
        //steering.second = getNewOrientation(character->ang, steering.second);

        return steering;
}

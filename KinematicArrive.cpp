#include "KinematicArrive.hpp"
#include "Ent.hpp"

KinematicArrive::KinematicArrive(Ent *character, Ent *target, double maxSpeed, double radius) {
        this->character = character;
        this->target    = target   ;
        this->maxSpeed  = maxSpeed ;
        this->radius    = radius   ;
        this->dead      = false    ;
}

pair<bool, Triple> KinematicArrive::getVel(unsigned int ticks) {
        pair<bool, Triple> steering;
        Triple cp, tp;

        steering.first = false;

        tie(cp, tp) = points(this->character, this->target);
        steering.second = tp - cp;

        if (steering.second.length() > radius) {
                steering.first = true;
                steering.second /= timeToTarget;
                if (steering.second.length() > maxSpeed) {
                        steering.second.normalized();
                        steering.second *= maxSpeed;
                }
        }

        return steering;
}

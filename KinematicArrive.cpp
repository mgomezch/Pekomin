#include "KinematicArrive.hpp"
#include "Ent.hpp"

KinematicArrive::KinematicArrive(Ent *character, Ent *target, double maxSpeed, double radius) {
        this->character = character;
        this->target    = target;
        this->maxSpeed  = maxSpeed;
        this->radius    = radius;
}

pair<bool, Triple> KinematicArrive::getVel(unsigned int ticks) {
        pair<bool, Triple> steering;

        steering.first = false;

        steering.second = target->pos - character->pos;

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

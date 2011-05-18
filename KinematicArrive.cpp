#include "KinematicArrive.hpp"
#include "Ent.hpp"

KinematicArrive::KinematicArrive(Ent *character, Ent *target, double maxSpeed, double radius) {
        this->character = character;
        this->target    = target;
        this->maxSpeed  = maxSpeed;
        this->radius    = radius;
}

tuple<bool, Triple, double> KinematicArrive::getVel(unsigned int ticks) {
        tuple<bool, Triple, double> steering;

        get<0>(steering) = false;
        get<2>(steering) = 0;

        get<1>(steering) = target->pos - character->pos;

        if (get<1>(steering).length() > radius) {
                get<0>(steering) = true;
                get<1>(steering) /= timeToTarget;
                if (get<1>(steering).length() > maxSpeed) {
                        get<1>(steering).normalized();
                        get<1>(steering) *= maxSpeed;
                }
        }

        return steering;
}

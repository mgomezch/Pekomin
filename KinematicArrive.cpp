#include "KinematicArrive.hpp"

KinematicArrive::KinematicArrive(Ent *character_, Ent *target_, double maxSpeed_, double radius_) {
        character = character_;
        target    = target_;
        maxSpeed  = maxSpeed_;
        radius    = radius_;
}

pair<Triple,double> KinematicArrive::getSteering() {
        pair<Triple, double> steering;
        steering.first = target->pos - character->pos;

        //cuando no se cumple esto que se retorna? o que tiene el steering?
        if (steering.first.length() >= radius) {
                steering.first /= timeToTarget;

                if (steering.first.length() > maxSpeed) {
                        steering.first.normalize();
                        steering.first *= maxSpeed;
                }

                character->ang = getNewOrientation(character->ang, steering.first);

                steering.second = 0;
        }

        return steering;
}

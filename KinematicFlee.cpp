#include "KinematicFlee.hpp"
#include "Ent.hpp"

KinematicFlee::KinematicFlee(Ent *character_, Ent *target_, double maxSpeed_) {
        character = character_;
        target    = target_;
        maxSpeed  = maxSpeed_;
}

// Retorna incrementos de velocidad y rotación
pair<bool, Triple> KinematicFlee::getVelIncr(unsigned int ticks) {
        pair<bool, Triple> steering;

        steering.second = character->pos - target->pos;
        if (steering.second.length() < 3) {
                steering.first = true;
                steering.second.normalize();
                steering.second *= maxSpeed;
        }
        else {
                steering.first = false;
        }

        return steering;
}

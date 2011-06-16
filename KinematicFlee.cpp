#include "KinematicFlee.hpp"
#include "Ent.hpp"

KinematicFlee::KinematicFlee(Ent *character, Ent *target, double maxSpeed, double fleeRadius) {
        this->character  = character ;
        this->target     = target    ;
        this->maxSpeed   = maxSpeed  ;
        this->fleeRadius = fleeRadius;
        this->dead       = false     ;
}

// Retorna incrementos de velocidad y rotación
pair<bool, Triple> KinematicFlee::getVelIncr(unsigned int ticks) {
        pair<bool, Triple> steering;

        steering.second = character->pos - target->pos;
        if (steering.second.length() < fleeRadius) {
                steering.first = true;
                steering.second.normalize();
                steering.second *= maxSpeed;
        }
        else {
                steering.first = false;
        }

        return steering;
}

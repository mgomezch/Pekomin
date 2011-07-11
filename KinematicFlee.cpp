#include "Ent.hpp"
#include "KinematicFlee.hpp"
#include "Triple.hpp"

KinematicFlee::KinematicFlee(Ent *character, Ent *target, double maxSpeed, double fleeRadius) {
        this->character  = character ;
        this->target     = target    ;
        this->maxSpeed   = maxSpeed  ;
        this->fleeRadius = fleeRadius;
}

// Retorna incrementos de velocidad y rotación
pair<bool, Triple> KinematicFlee::getVelIncr(unsigned int ticks) {
        pair<bool, Triple> steering;
        Triple cp, tp;

        tie(cp, tp) = points(this->character, this->target);
        steering.second = cp - tp;
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

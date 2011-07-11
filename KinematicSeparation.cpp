#include "Ent.hpp"
#include "KinematicSeparation.hpp"
#include "Triple.hpp"

KinematicSeparation::KinematicSeparation(Ent *character, Ent *target, double maxSpeed, double separationRadius) {
        this->character  = character             ;
        this->target     = target                ;
        this->maxSpeed   = maxSpeed              ;
        this->separationRadius = separationRadius;
        this->active     = true                  ;
}

// Retorna incrementos de velocidad y rotación
pair<bool, Triple> KinematicSeparation::getVelIncr(unsigned int ticks) {
        pair<bool, Triple> steering;
        Triple cp, tp;

        tie(cp, tp) = points(this->character, this->target);
        steering.second = cp - tp;
        if (steering.second.length() < separationRadius) {
                steering.first = true;
                steering.second.normalize();
                steering.second *= maxSpeed;
        }
        else {
                steering.first = false;
        }

        return steering;
}

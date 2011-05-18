#include "KinematicFlee.hpp"
#include "Ent.hpp"

KinematicFlee::KinematicFlee(Ent *character_, Ent *target_, double maxSpeed_) {
        character = character_;
        target    = target_;
        maxSpeed  = maxSpeed_;
}

// Retorna incrementos de velocidad y rotación
tuple<bool, Triple, double> KinematicFlee::getVelIncr(unsigned int ticks) {
        tuple<bool, Triple, double> steering;
        get<1>(steering) = character->pos - target->pos;
        get<1>(steering).normalize();
        get<1>(steering) *= maxSpeed;
//      character->ang = getNewOrientation(character->ang, get<1>(steering));
        get<2>(steering) = 0;

        return steering;
}

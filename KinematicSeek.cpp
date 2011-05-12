#include "KinematicSeek.hpp"
#include "Ent.hpp"

KinematicSeek::KinematicSeek(Ent *character_, Ent *target_, double maxSpeed_) {
        character = character_;
        target    = target_;
        maxSpeed  = maxSpeed_;
}

// Retorna incrementos de velocidad y rotacion
tuple<bool, Triple,double> KinematicSeek::getVelIncr() {
        tuple<bool, Triple, double> steering;
        get<1>(steering) = target->pos - character->pos;
        get<1>(steering).normalize();
        get<1>(steering) *= maxSpeed;
        //get<2>(steering) = getNewOrientation(character->ang, get<1>(steering));

        return steering;
}

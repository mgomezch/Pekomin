#include "KinematicSeek.hpp"
#include "Ent.hpp"

unsigned int KinematicSeek::type() {
        return BEHAVIOR_KINEMATICSEEK;
}

KinematicSeek::KinematicSeek(Ent *character, Ent *target, double maxSpeed) {
        this->character = character;
        this->target    = target   ;
        this->maxSpeed  = maxSpeed ;
}

tuple<bool, Triple,double> KinematicSeek::getVelIncr() {
        tuple<bool, Triple, double> steering;
        get<0>(steering) = true;
        get<1>(steering) = target->pos - character->pos;
        get<1>(steering).normalize();
        get<1>(steering) *= maxSpeed;
        //get<2>(steering) = getNewOrientation(character->ang, get<1>(steering));

        return steering;
}

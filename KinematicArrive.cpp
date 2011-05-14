#include "KinematicArrive.hpp"
#include "Ent.hpp"

unsigned int KinematicArrive::type() {
        return BEHAVIOR_KINEMATICARRIVE;
}

KinematicArrive::KinematicArrive(Ent *character_, Ent *target_, double maxSpeed_, double radius_) {
        character = character_;
        target    = target_;
        maxSpeed  = maxSpeed_;
        radius    = radius_;
}

tuple<bool, Triple, double> KinematicArrive::getVelIncr() {
        tuple<bool, Triple, double> steering;
        get<1>(steering) = target->pos - character->pos;

        //cuando no se cumple esto que se retorna? o que tiene el steering? o usar una referencia e instanciar a NULL y echarnos agua :D
        if (get<1>(steering).length() >= radius) {
                get<1>(steering) /= timeToTarget;
//              get<2>(steering) = getNewOrientation(character->ang, get<1>(steering));
        }

        return steering;
}

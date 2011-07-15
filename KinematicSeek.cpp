#include "Ent.hpp"
#include "KinematicSeek.hpp"
#include "Triple.hpp"

KinematicSeek::KinematicSeek(Ent *character, Ent *target, double maxSpeed):
        character(character),
        target(target),
        maxSpeed(maxSpeed)
{}

pair<bool, Triple> KinematicSeek::getVelIncr(unsigned int ticks) {
        pair<bool, Triple> steering;
        Triple cp, tp;

        steering.first = true;
        tie(cp, tp) = points(this->character, this->target);
        steering.second = tp - cp;
        steering.second.normalize();
        steering.second *= maxSpeed;
        //steering.second = getNewOrientation(character->ang, steering.second);

        return steering;
}

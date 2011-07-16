#include <vector>

#include "Ent.hpp"
#include "KinematicSeek.hpp"
#include "Triple.hpp"

KinematicSeek::KinematicSeek(string name, Ent *character, Ent *target, double maxSpeed):
        KinematicV(name),
        character(character),
        target(target),
        maxSpeed(maxSpeed)
{}

vector<Triple> KinematicSeek::getVelIncr(unsigned int ticks) {
        Triple cp, tp;

        tie(cp, tp) = points(this->character, this->target);

        return vector<Triple>(1, (tp - cp).normalized() * maxSpeed);
}

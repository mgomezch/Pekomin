#include <vector>

#include "Ent.hpp"
#include "KinematicSeek.hpp"
#include "Triple.hpp"

KinematicSeek::KinematicSeek(std::string name, Ent *character, Ent *target, double maxSpeed):
        KinematicV(name),
        character(character),
        target(target),
        maxSpeed(maxSpeed)
{}

std::vector<Triple> KinematicSeek::getVelIncr(unsigned int ticks, unsigned int delta_ticks) {
        Triple cp, tp;

        std::tie(cp, tp) = points(this->character, this->target);

        return std::vector<Triple>(1, (tp - cp).normalized() * maxSpeed);
}

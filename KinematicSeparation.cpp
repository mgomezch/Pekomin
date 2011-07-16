#include <vector>

#include "Ent.hpp"
#include "KinematicSeparation.hpp"
#include "Triple.hpp"

KinematicSeparation::KinematicSeparation(std::string name, Ent *character, Ent *target, double maxSpeed, double separationRadius):
        KinematicV(name),
        character(character),
        target(target),
        maxSpeed(maxSpeed),
        separationRadius(separationRadius)
{}

std::vector<Triple> KinematicSeparation::getVelIncr(unsigned int ticks, unsigned int delta_ticks) {
        Triple steering;
        Triple cp, tp;

        std::tie(cp, tp) = points(this->character, this->target);
        steering = cp - tp;
        if (steering.length() < separationRadius) {
                steering.normalize();
                steering *= maxSpeed;
                return std::vector<Triple>(1, steering);
        }
        return std::vector<Triple>();
}

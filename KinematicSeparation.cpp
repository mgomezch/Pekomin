#include <vector>

#include "Ent.hpp"
#include "KinematicSeparation.hpp"
#include "Triple.hpp"

KinematicSeparation::KinematicSeparation(string name, Ent *character, Ent *target, double maxSpeed, double separationRadius):
        KinematicV(name),
        character(character),
        target(target),
        maxSpeed(maxSpeed),
        separationRadius(separationRadius)
{}

vector<Triple> KinematicSeparation::getVelIncr(unsigned int ticks) {
        Triple steering;
        Triple cp, tp;

        tie(cp, tp) = points(this->character, this->target);
        steering = cp - tp;
        if (steering.length() < separationRadius) {
                steering.normalize();
                steering *= maxSpeed;
                return vector<Triple>(1, steering);
        }
        return vector<Triple>();
}

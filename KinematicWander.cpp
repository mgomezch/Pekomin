#include <cmath>

#include "KinematicWander.hpp"
#include "Ent.hpp"
#include "Triple.hpp"
#include "util.hpp"

KinematicWander::KinematicWander(string name, Ent *character, double maxSpeed, double maxRotation, double wanderTime):
        DirectKinematicV(name),
        character(character),
        maxSpeed(maxSpeed),
        maxRotation(maxRotation),
        wanderTime(wanderTime),
        accum(0)
{}

pair<bool, Triple> KinematicWander::getVel(unsigned int ticks) {
        pair<bool, Triple> steering;
        double ang;

        if (this->accum == 0) {
               ang = RandBin(-1,1) * maxRotation;
        }
        if ((this->accum += ticks) >= wanderTime) this->accum = 0;

        steering.first = true;
        steering.second = Triple(cos(ang), sin(ang), 0) * maxSpeed;

        return steering;
}

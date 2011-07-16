#include <cmath>
#include <vector>

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

vector<Triple> KinematicWander::getVel(unsigned int ticks) {
        Triple steering;
        double ang;

        if (this->accum == 0) {
               ang = RandBin(-1,1) * maxRotation;
        }
        if ((this->accum += ticks) >= wanderTime) this->accum = 0;

        return vector<Triple>(1, Triple(cos(ang), sin(ang), 0) * maxSpeed);
}

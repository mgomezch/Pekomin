#include "KinematicWander.hpp"
#include "Ent.hpp"
#include "util.hpp"

KinematicWander::KinematicWander(Ent *character, double maxSpeed, double maxRotation) {
        this->character   = character  ;
        this->maxSpeed    = maxSpeed   ;
        this->maxRotation = maxRotation;
        this->accum       = 0          ;
        this->dead        = false      ;
}

pair<bool, Triple> KinematicWander::getVel(unsigned int ticks) {
        pair<bool, Triple> steering;

        if (this->accum == 0) {
               character->ang = RandBin(-1,1) * maxRotation;
        }
        if ((this->accum += ticks) >= 3000) this->accum = 0;

        steering.first = true;
        steering.second = character->orientation() * maxSpeed;
        steering.second.normalized();// = randomBinomial()         * maxRotation;

        return steering;
}

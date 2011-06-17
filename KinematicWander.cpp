#include "KinematicWander.hpp"
#include "Ent.hpp"
#include "util.hpp"

KinematicWander::KinematicWander(Ent *character, double maxSpeed, double maxRotation, double wanderTime) {
        this->character   = character  ;
        this->maxSpeed    = maxSpeed   ;
        this->maxRotation = maxRotation;
        this->accum       = 0          ;
        this->wanderTime  = wanderTime ;
        this->dead        = false      ;
}

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

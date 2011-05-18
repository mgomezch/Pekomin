#include "Wander.hpp"
#include "Mobile.hpp"
#include "util.hpp"
#include "Phantom.hpp"

Wander::Wander(Mobile *character            ,
               double maxAngularAcceleration,
               double maxRotation           ,
               double targetRadius          ,
               double slowRadius            ,
               double wanderOffset          ,
               double wanderRadius          ,
               double wanderRate            ,
               double wanderOrientation     ,
               double maxAcceleration       ) {
        this->character              = character;
        this->target                 = new Phantom();
        this->maxAngularAcceleration = maxAngularAcceleration;
        this->maxRotation            = maxRotation;
        this->targetRadius           = targetRadius;
        this->slowRadius             = slowRadius;
        this->wanderOffset           = wanderOffset;
        this->wanderRadius           = wanderRadius;
        this->wanderRate             = wanderRate;
        this->wanderOrientation      = wanderOrientation;
        this->maxAcceleration        = maxAcceleration;
        this->accum                  = 0;
}

tuple<bool, Triple, double> Wander::getVelIncr(unsigned int ticks) {
        tuple<bool, Triple, double> steering;

        if (this->accum == 0) {
                wanderOrientation += randomBinomial() * wanderRate;
                target->ang = character->ang * wanderOrientation;
                target->pos = character->pos; //+ character->orientation() * wanderOffset;
                target->pos += target->orientation() * wanderRadius;
        }
        if ((this->accum += ticks) >= 3000) this->accum = 0;
        
        //steering = Face::getVelIncr();
        get<0>(steering) = true;
        get<1>(steering) = target->pos - character->pos;
        get<1>(steering).normalize();
        get<1>(steering) *= maxAcceleration;

        return steering;
}

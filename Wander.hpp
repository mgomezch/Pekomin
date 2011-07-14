#ifndef WANDER_HPP
#define WANDER_HPP

#include "DirectKinematicV.hpp"
#include "Triple.hpp"

class Mobile;

class Wander : public DirectKinematicV {
        public:
                Mobile* character;
                Mobile* target;
                double maxRotation;
                double targetRadius;
                double slowRadius;
                double wanderOffset;
                double wanderRadius;
                double wanderRate;
                double wanderTime;
                double wanderOrientation;
                double maxSpeed;
                unsigned int accum;

                Wander(Mobile *character  ,
                       double maxRotation ,
                       double targetRadius,
                       double slowRadius  ,
                       double wanderOffset,
                       double wanderRadius,
                       double wanderRate  ,
                       double wanderTime  ,
                       double maxSpeed    );

                virtual pair<bool, Triple> getVel(unsigned int ticks);
};

#endif

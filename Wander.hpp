#ifndef _WANDER_HPP
#define _WANDER_HPP

#include "KinematicV.hpp"
#include "Mobile.hpp"

class Wander : public KinematicV {
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

                virtual pair<bool, Triple> getVelIncr(unsigned int ticks);
};

#endif

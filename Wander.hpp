#ifndef WANDER_HPP
#define WANDER_HPP

#include "DirectKinematicV.hpp"
#include "Triple.hpp"

class Mobile;

class Wander : public DirectKinematicV {
        public:
                Mobile* character;
                double maxRotation;
                double targetRadius;
                double slowRadius;
                double wanderOffset;
                double wanderRadius;
                double wanderRate;
                double wanderTime;
                double maxSpeed;

                Mobile* target;
                double wanderOrientation;
                unsigned int accum;

                Wander(Mobile *character, double maxRotation, double targetRadius, double slowRadius, double wanderOffset, double wanderRadius, double wanderRate, double wanderTime, double maxSpeed);

                virtual pair<bool, Triple> getVel(unsigned int ticks);
};

#endif

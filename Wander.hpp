#ifndef WANDER_HPP
#define WANDER_HPP

#include "DirectKinematicV.hpp"
#include "Triple.hpp"

class Mobile;

class Wander : public virtual DirectKinematicV {
        public:
                Mobile *character;
                double maxRotation;
                double targetRadius;
                double slowRadius;
                double wanderOffset;
                double wanderRadius;
                double wanderRate;
                double wanderTime;
                double maxSpeed;

                Mobile *target;
                unsigned int accum;
                double wanderOrientation;

                Wander(string name, Mobile *character, double maxRotation, double targetRadius, double slowRadius, double wanderOffset, double wanderRadius, double wanderRate, double wanderTime, double maxSpeed);

                virtual vector<Triple> getVel(unsigned int ticks);
};

#endif

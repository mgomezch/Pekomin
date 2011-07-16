#ifndef WANDER_HPP
#define WANDER_HPP

#include <vector>

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

                Wander(std::string name, Mobile *character, double maxRotation, double targetRadius, double slowRadius, double wanderOffset, double wanderRadius, double wanderRate, double wanderTime, double maxSpeed);

                virtual std::vector<Triple> getVel(unsigned int ticks, unsigned int delta_ticks);
};

#endif

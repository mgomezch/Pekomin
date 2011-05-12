#ifndef _WANDER_HPP
#define _WANDER_HPP

#include "Face.hpp"

class Wander : public Face {
        public:
                static const unsigned int type = BEHAVIOR_WANDER;
                double wanderOffset;
                double wanderRadius;
                double wanderRate;
                double wanderOrientation;
                double maxAcceleration;

                Wander(Mobile *character, Mobile *target, double maxAngularAcceleration, double maxRotation, double targetRadius, double slowRadius, double wanderOffset, double wanderRadius, double wanderRate, double wanderOrientation, double maxAcceleration);

                tuple<bool, Triple, double> getVelIncr();
};

#endif

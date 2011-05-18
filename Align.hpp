#ifndef _ALIGN_HPP
#define _ALIGN_HPP

#include "Kinematic.hpp"

using namespace std;

class Mobile;

class Align : public Kinematic {
        public:
                Mobile *character;
                Mobile *target;
                double maxAngularAcceleration;
                double maxRotation;
                double targetRadius;
                double slowRadius;
                static const double timeToTarget = 0.1;

                Align(Mobile *character, Mobile *target, double maxAngularAcceleration, double maxRotation, double targetRadius, double slowRadius);

                virtual tuple<bool, Triple, double> getVelIncr(unsigned int ticks);
                void mapToRange(double *value);
};

#endif

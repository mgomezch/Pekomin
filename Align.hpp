#ifndef _ALIGN_HPP
#define _ALIGN_HPP

#include "Behavior.hpp"

using namespace std;

class Mobile;

class Align : Behavior {
        public:
                static const unsigned int type = BEHAVIOR_ALIGN;
                Mobile *character;
                Mobile *target;
                double maxAngularAcceleration;
                double maxRotation;
                double targetRadius;
                double slowRadius;
                static const double timeToTarget = 0.1;

                Align(Mobile *character, Mobile *target, double maxAngularAcceleration, double maxRotation, double targetRadius, double slowRadius);

                void mapToRange(double *value);
                pair<Triple, double> getSteering();
};

#endif

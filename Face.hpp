#ifndef _FACE_HPP
#define _FACE_HPP

#include "Kinematic.hpp"

using namespace std;

class Mobile;

class Face : public Kinematic {
        public:
                static const unsigned int type = BEHAVIOR_FACE;
                Mobile *character;
                Mobile *target;
                double maxAngularAcceleration;
                double maxRotation;
                double targetRadius;
                double slowRadius;
                static const double timeToTarget = 0.1;

                Face(Mobile *character, Mobile *target, double maxAngularAcceleration, double maxRotation, double targetRadius, double slowRadius);

                virtual tuple<bool, Triple, double> getVelIncr();
                void mapToRange(double *value);
};

#endif

#ifndef _FACE_HPP
#define _FACE_HPP

#include "Kinematic.hpp"

using namespace std;

class Mobile;

class Face : public Kinematic {
        public:
                Mobile *character;
                Mobile *target;
                double maxAngularVelocity;
                double targetRadius;
                double slowRadius;

                Face(Mobile *character, Mobile *target, double maxAngularVelocity, double targetRadius, double slowRadius);

                virtual tuple<bool, Triple, double> getVelIncr(unsigned int ticks);
};

#endif

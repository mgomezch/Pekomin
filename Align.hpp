#ifndef _ALIGN_HPP
#define _ALIGN_HPP

#include "Kinematic.hpp"

using namespace std;

class Mobile;

class Align : public Kinematic {
        public:
                Mobile *character;
                Mobile *target;
                double maxAngularVelocity;
                double targetRadius;
                double slowRadius;

                Align(Mobile *character, Mobile *target, double maxAngularVelocity, double targetRadius, double slowRadius);

                virtual tuple<bool, Triple, double> getVelIncr(unsigned int ticks);
};

#endif

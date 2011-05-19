#ifndef _LOOKWHEREYOUREGOING_HPP
#define _LOOKWHEREYOUREGOING_HPP

#include "Kinematic.hpp"

using namespace std;

class Mobile;

class LookWhereYoureGoing : public Kinematic {
        public:
                Mobile *character;
                Mobile *target;
                double maxAngularVelocity;
                double targetRadius;
                double slowRadius;

                LookWhereYoureGoing(Mobile *character, double maxAngularVelocity, double targetRadius, double slowRadius);

                virtual tuple<bool, Triple, double> getVelIncr(unsigned int ticks);
};

#endif

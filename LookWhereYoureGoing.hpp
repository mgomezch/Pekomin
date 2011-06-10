#ifndef _LOOKWHEREYOUREGOING_HPP
#define _LOOKWHEREYOUREGOING_HPP

#include "KinematicA.hpp"

using namespace std;

class Mobile;

class LookWhereYoureGoing : public KinematicA {
        public:
                Mobile *character;
                Mobile *target;
                double maxAngularVelocity;
                double targetRadius;
                double slowRadius;

                LookWhereYoureGoing(Mobile *character, double maxAngularVelocity, double targetRadius, double slowRadius);

                virtual pair<bool, double> getAngVelIncr(unsigned int ticks);
};

#endif

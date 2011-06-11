#ifndef _LOOKWHEREYOUREGOING_HPP
#define _LOOKWHEREYOUREGOING_HPP

#include "DirectKinematicA.hpp"

using namespace std;

class Mobile;

class LookWhereYoureGoing : public DirectKinematicA {
        public:
                Mobile *character;
                Mobile *target;
                double maxAngularVelocity;
                double targetRadius;
                double slowRadius;

                LookWhereYoureGoing(Mobile *character, double maxAngularVelocity, double targetRadius, double slowRadius);

                virtual pair<bool, double> getAngVel(unsigned int ticks);
};

#endif

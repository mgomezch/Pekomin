#ifndef _ALIGN_HPP
#define _ALIGN_HPP

#include "DirectKinematicA.hpp"

using namespace std;

class Mobile;

class Align : public DirectKinematicA {
        public:
                Mobile *character;
                Mobile *target;
                double maxAngularVelocity;
                double targetRadius;
                double slowRadius;

                Align(Mobile *character, Mobile *target, double maxAngularVelocity, double targetRadius, double slowRadius);

                virtual pair<bool, double> getAngVel(unsigned int ticks);
};

#endif

#ifndef _ALIGN_HPP
#define _ALIGN_HPP

#include "KinematicA.hpp"

using namespace std;

class Mobile;

class Align : public KinematicA {
        public:
                Mobile *character;
                Mobile *target;
                double maxAngularVelocity;
                double targetRadius;
                double slowRadius;

                Align(Mobile *character, Mobile *target, double maxAngularVelocity, double targetRadius, double slowRadius);

                virtual pair<bool, double> getAngVelIncr(unsigned int ticks);
};

#endif

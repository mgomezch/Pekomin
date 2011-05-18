#ifndef _FLEE_HPP
#define _FLEE_HPP

#include "Kinematic.hpp"

using namespace std;

class Mobile;

class Flee : public Kinematic {
        public:
                Mobile *character;
                Mobile *target;
                double maxAcceleration;
                double fleeRadius;

                Flee(Mobile *character, Mobile *target, double maxAcceleration, double fleeRadius);

                virtual tuple<bool, Triple, double> getVelIncr(unsigned int ticks);
};

#endif

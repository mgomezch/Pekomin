#ifndef _FLEE_HPP
#define _FLEE_HPP

#include "KinematicV.hpp"

using namespace std;

class Mobile;

class Flee : public KinematicV {
        public:
                Mobile *character;
                Mobile *target;
                double maxSpeed;
                double fleeRadius;

                Flee(Mobile *character, Mobile *target, double maxSpeed, double fleeRadius);

                virtual pair<bool, Triple> getVelIncr(unsigned int ticks);
};

#endif

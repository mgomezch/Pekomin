#ifndef _FLEE_HPP
#define _FLEE_HPP

#include "DirectKinematicV.hpp"
#include "Triple.hpp"

using namespace std;

class Mobile;

class Flee : public DirectKinematicV {
        public:
                Mobile *character;
                Mobile *target;
                double maxSpeed;
                double fleeRadius;

                Flee(Mobile *character, Mobile *target, double maxSpeed, double fleeRadius);

                virtual pair<bool, Triple> getVel(unsigned int ticks);
};

#endif

#ifndef STATICVELOCITYMATCH_HPP
#define STATICVELOCITYMATCH_HPP

#include "DirectKinematicV.hpp"
#include "Triple.hpp"

using namespace std;

class Mobile;

class StaticVelocityMatch : public DirectKinematicV {
        public:
                Mobile *character;
                Mobile *target;

                StaticVelocityMatch(Mobile *character, Mobile *target);

                virtual pair<bool, Triple> getVel(unsigned int ticks);
};

#endif

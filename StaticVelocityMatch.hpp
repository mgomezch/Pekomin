#ifndef _STATICVELOCITYMATCH_HPP
#define _STATICVELOCITYMATCH_HPP

#include "DirectKinematicV.hpp"

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

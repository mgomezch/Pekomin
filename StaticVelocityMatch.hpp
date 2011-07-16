#ifndef STATICVELOCITYMATCH_HPP
#define STATICVELOCITYMATCH_HPP

#include "DirectKinematicV.hpp"
#include "Triple.hpp"

using namespace std;

class Mobile;

class StaticVelocityMatch : public virtual DirectKinematicV {
        public:
                Mobile *character;
                Mobile *target;

                StaticVelocityMatch(string name, Mobile *character, Mobile *target);

                virtual vector<Triple> getVel(unsigned int ticks);
};

#endif

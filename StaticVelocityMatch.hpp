#ifndef STATICVELOCITYMATCH_HPP
#define STATICVELOCITYMATCH_HPP

#include <vector>

#include "DirectKinematicV.hpp"
#include "Triple.hpp"

class Mobile;

class StaticVelocityMatch : public virtual DirectKinematicV {
        public:
                Mobile *character;
                Mobile *target;

                StaticVelocityMatch(std::string name, Mobile *character, Mobile *target);

                virtual std::vector<Triple> getVel(unsigned int ticks, unsigned int delta_ticks);
};

#endif

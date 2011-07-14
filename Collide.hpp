#ifndef COLLIDE_HPP
#define COLLIDE_HPP

#include "KinematicV.hpp"
#include "StaticV.hpp"
#include "Triple.hpp"

using namespace std;

class Mobile;

class Collide : public virtual KinematicV, public virtual StaticV {
        public:
                Mobile *character;
                Mobile *target;

                Collide(Mobile *character, Mobile *target);

                virtual pair<bool, Triple> getPosIncr(unsigned int ticks);
                virtual pair<bool, Triple> getVelIncr(unsigned int ticks);
};

#endif

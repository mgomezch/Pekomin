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

                Collide(string name, Mobile *character, Mobile *target);

                virtual vector<Triple> getPosIncr(unsigned int ticks);
                virtual vector<Triple> getVelIncr(unsigned int ticks);
};

#endif

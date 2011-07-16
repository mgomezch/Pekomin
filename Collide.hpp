#ifndef COLLIDE_HPP
#define COLLIDE_HPP

#include "KinematicV.hpp"
#include "StaticV.hpp"
#include "Triple.hpp"

class Mobile;

class Collide : public virtual KinematicV, public virtual StaticV {
        public:
                Mobile *character;
                Mobile *target;

                Collide(std::string name, Mobile *character, Mobile *target);

                virtual std::vector<Triple> getPosIncr(unsigned int ticks, unsigned int delta_ticks);
                virtual std::vector<Triple> getVelIncr(unsigned int ticks, unsigned int delta_ticks);
};

#endif

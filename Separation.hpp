#ifndef SEPARATION_HPP
#define SEPARATION_HPP

#include <vector>

#include "KinematicV.hpp"
#include "Triple.hpp"

class Mobile;

class Separation : public virtual KinematicV {
        public:
                Mobile *character;
                Mobile *target;
                double maxSpeed;
                double separationRadius;

                Separation(std::string name, Mobile *character, Mobile *target, double maxSpeed, double separationRadius);

                virtual std::vector<Triple> getVelIncr(unsigned int ticks, unsigned int delta_ticks);
};

#endif

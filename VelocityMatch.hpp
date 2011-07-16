#ifndef VELOCITYMATCH_HPP
#define VELOCITYMATCH_HPP

#include <vector>

#include "KinematicV.hpp"
#include "Triple.hpp"

class Mobile;

class VelocityMatch : public virtual KinematicV {
        public:
                Mobile *character;
                Mobile *target;
                double maxSpeed;
                static const double timeToTarget = 0.1;

                VelocityMatch(std::string name, Mobile *character, Mobile *target, double maxSpeed);

                virtual std::vector<Triple> getVelIncr(unsigned int ticks, unsigned int delta_ticks);
};

#endif

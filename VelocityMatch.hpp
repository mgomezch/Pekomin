#ifndef VELOCITYMATCH_HPP
#define VELOCITYMATCH_HPP

#include <utility>

#include "KinematicV.hpp"
#include "Triple.hpp"

using namespace std;

class Mobile;

class VelocityMatch : public virtual KinematicV {
        public:
                Mobile *character;
                Mobile *target;
                double maxSpeed;
                static const double timeToTarget = 0.1;

                VelocityMatch(Mobile *character, Mobile *target, double maxSpeed);

                virtual pair<bool, Triple> getVelIncr(unsigned int ticks);
};

#endif

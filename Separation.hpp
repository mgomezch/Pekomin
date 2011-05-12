#ifndef _SEPARATION_HPP
#define _SEPARATION_HPP

#include <tuple>

#include "Kinematic.hpp"

class Mobile;

class Separation : public Kinematic {
        public:
                static const unsigned int type = BEHAVIOR_SEPARATION;
                Mobile *character;
                Mobile *target;
                double threshold;
                double decayCoefficient;
                double maxAcceleration;

                Separation(Mobile *character, Mobile *target, double threshold, double decayCoefficient, double maxAcceleration);

                tuple<bool, Triple, double> getVelIncr();
};

#endif

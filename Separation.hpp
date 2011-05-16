#ifndef _SEPARATION_HPP
#define _SEPARATION_HPP

#include <tuple>

#include "Kinematic.hpp"

class Mobile;

class Separation : public Kinematic {
        public:
                Mobile *character;
                Mobile *target;
                double threshold;
                double decayCoefficient;
                double maxAcceleration;

                Separation(Mobile *character, Mobile *target, double threshold, double decayCoefficient, double maxAcceleration);
//              virtual unsigned int type();

                tuple<bool, Triple, double> getVelIncr();
};

#endif

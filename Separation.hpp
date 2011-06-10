#ifndef _SEPARATION_HPP
#define _SEPARATION_HPP

#include "KinematicV.hpp"

class Mobile;

class Separation : public KinematicV {
        public:
                Mobile *character;
                Mobile *target;
                double threshold;
                double decayCoefficient;
                double maxAcceleration;

                Separation(Mobile *character, Mobile *target, double threshold, double decayCoefficient, double maxAcceleration);

                virtual pair<bool, Triple> getVelIncr(unsigned int ticks);
};

#endif

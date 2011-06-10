#ifndef _PURSUE_HPP
#define _PURSUE_HPP

#include "KinematicV.hpp"

using namespace std;

class Mobile;

class Pursue : public KinematicV {
        public:
                Mobile *character;
                Mobile *target;
                double maxAcceleration;
                static const double maxPrediction = 0.01;

                Pursue(Mobile *character, Mobile *target, double maxAcceleration);

                virtual pair<bool, Triple> getVelIncr(unsigned int ticks);
};

#endif

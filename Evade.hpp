#ifndef _EVADE_HPP
#define _EVADE_HPP

#include "KinematicV.hpp"

using namespace std;

class Mobile;

class Evade : public KinematicV {
        public:
                Mobile *character;
                Mobile *target;
                double maxAcceleration;
                static const double maxPrediction = 0.01;

                Evade(Mobile *character, Mobile *target, double maxAcceleration);

                virtual pair<bool, Triple> getVelIncr(unsigned int ticks);
};

#endif

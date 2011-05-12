#ifndef _EVADE_HPP
#define _EVADE_HPP

#include "Kinematic.hpp"

using namespace std;

class Mobile;

class Evade : public Kinematic {
        public:
                static const unsigned int type = BEHAVIOR_EVADE;
                Mobile *character;
                Mobile *target;
                double maxAcceleration;
                double maxPrediction;

                Evade(Mobile *character, Mobile *target, double maxAcceleration);

                virtual tuple<bool, Triple, double> getVelIncr();
};

#endif

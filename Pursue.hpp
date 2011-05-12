#ifndef _PURSUE_HPP
#define _PURSUE_HPP

#include "Kinematic.hpp"

using namespace std;

class Mobile;

class Pursue : public Kinematic {
        public:
                static const unsigned int type = BEHAVIOR_PURSUE;
                Mobile *character;
                Mobile *target;
                double maxAcceleration;
                double maxPrediction;

                Pursue(Mobile *character, Mobile *target, double maxAcceleration);
};

#endif

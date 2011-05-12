#ifndef _FLEE_HPP
#define _FLEE_HPP

#include "Behavior.hpp"

using namespace std;

class Mobile;

class Flee : public Kinematic {
        public:
                static const unsigned int type = BEHAVIOR_FLEE;
                Mobile *character;
                Mobile *target;
                double maxAcceleration;

                Flee(Mobile *character, Mobile *target, double maxAcceleration);
};

#endif

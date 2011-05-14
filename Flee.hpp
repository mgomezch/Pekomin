#ifndef _FLEE_HPP
#define _FLEE_HPP

#include "Kinematic.hpp"

using namespace std;

class Mobile;

class Flee : public Kinematic {
        public:
                Mobile *character;
                Mobile *target;
                double maxAcceleration;

                Flee(Mobile *character, Mobile *target, double maxAcceleration);
                virtual unsigned int type();

                virtual tuple<bool, Triple, double> getVelIncr();
};

#endif

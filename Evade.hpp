#ifndef _EVADE_HPP
#define _EVADE_HPP

#include "Kinematic.hpp"

using namespace std;

class Mobile;

class Evade : public Kinematic {
        public:
                Mobile *character;
                Mobile *target;
                double maxAcceleration;
                static const double maxPrediction = 0.01;

                Evade(Mobile *character, Mobile *target, double maxAcceleration);
//              virtual unsigned int type();

                virtual tuple<bool, Triple, double> getVelIncr();
};

#endif

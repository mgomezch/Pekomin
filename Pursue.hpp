#ifndef _PURSUE_HPP
#define _PURSUE_HPP

#include "Kinematic.hpp"

using namespace std;

class Mobile;

class Pursue : public Kinematic {
        public:
                Mobile *character;
                Mobile *target;
                double maxAcceleration;
                static const double maxPrediction = 0.01;

                Pursue(Mobile *character, Mobile *target, double maxAcceleration);

                virtual tuple<bool, Triple, double> getVelIncr(unsigned int ticks);
};

#endif

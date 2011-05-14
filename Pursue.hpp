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
                double maxPrediction;

                Pursue(Mobile *character, Mobile *target, double maxAcceleration);
                virtual unsigned int type();

                virtual tuple<bool, Triple, double> getVelIncr();
};

#endif

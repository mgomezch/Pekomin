#ifndef _PURSUE_HPP
#define _PURSUE_HPP

#include "DirectKinematicV.hpp"

using namespace std;

class Mobile;

class Pursue : public DirectKinematicV {
        public:
                Mobile *character;
                Mobile *target;
                double maxSpeed;
                static const double maxPrediction = 10;

                Pursue(Mobile *character, Mobile *target, double maxSpeed);

                virtual pair<bool, Triple> getVel(unsigned int ticks);
};

#endif

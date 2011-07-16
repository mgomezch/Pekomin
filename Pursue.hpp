#ifndef PURSUE_HPP
#define PURSUE_HPP

#include "DirectKinematicV.hpp"
#include "Triple.hpp"

using namespace std;

class Mobile;

class Pursue : public virtual DirectKinematicV {
        public:
                Mobile *character;
                Mobile *target;
                double maxSpeed;

                static const double maxPrediction = 10;

                Pursue(string name, Mobile *character, Mobile *target, double maxSpeed);

                virtual vector<Triple> getVel(unsigned int ticks);
};

#endif

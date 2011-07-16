#ifndef EVADE_HPP
#define EVADE_HPP

#include "DirectKinematicV.hpp"
#include "Triple.hpp"

using namespace std;

class Mobile;

class Evade : public virtual DirectKinematicV {
        public:
                Mobile *character;
                Mobile *target;
                double maxSpeed;

                static const double maxPrediction = 10;

                Evade(string name, Mobile *character, Mobile *target, double maxSpeed);

                virtual vector<Triple> getVel(unsigned int ticks);
};

#endif

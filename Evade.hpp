#ifndef _EVADE_HPP
#define _EVADE_HPP

#include "Flee.hpp"

using namespace std;

class Mobile;

class Evade : public Flee {
        public:
                double maxPrediction;
                Mobile *target;

                pair<Triple, double> getSteering();
};

#endif

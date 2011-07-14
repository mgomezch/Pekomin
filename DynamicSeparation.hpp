#ifndef DYNAMICSEPARATION_HPP
#define DYNAMICSEPARATION_HPP

#include "DynamicV.hpp"
#include "Triple.hpp"

using namespace std;

class Mobile;

class DynamicSeparation : public DynamicV {
        public:
                Mobile *character;
                Mobile *target;
                double minForce;
                double separationRadius;

                DynamicSeparation(Mobile *character, Mobile *target, double minForce, double separationRadius);

                virtual pair<bool, Triple> getForce(unsigned int ticks);
};

#endif

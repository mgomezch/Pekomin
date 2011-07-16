#ifndef DYNAMICSEPARATION_HPP
#define DYNAMICSEPARATION_HPP

#include "DynamicV.hpp"
#include "Triple.hpp"

using namespace std;

class Mobile;

class DynamicSeparation : public virtual DynamicV {
        public:
                Mobile *character;
                Mobile *target;
                double minForce;
                double separationRadius;

                DynamicSeparation(string name, Mobile *character, Mobile *target, double minForce, double separationRadius);

                virtual vector<Triple> getForce(unsigned int ticks);
};

#endif

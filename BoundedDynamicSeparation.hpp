#ifndef BOUNDEDDYNAMICSEPARATION_HPP
#define BOUNDEDDYNAMICSEPARATION_HPP

#include "DynamicV.hpp"
#include "Triple.hpp"

using namespace std;

class Mobile;

class BoundedDynamicSeparation : public DynamicV {
        public:
                Mobile *character;
                Mobile *target;
                double maxForce;
                double separationRadius;

                BoundedDynamicSeparation(Mobile *character, Mobile *target, double maxForce, double separationRadius);

                virtual pair<bool, Triple> getForce(unsigned int ticks);
};

#endif

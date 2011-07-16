#ifndef BOUNDEDDYNAMICSEPARATION_HPP
#define BOUNDEDDYNAMICSEPARATION_HPP

#include <vector>

#include "DynamicV.hpp"
#include "Triple.hpp"

class Mobile;

class BoundedDynamicSeparation : public virtual DynamicV {
        public:
                Mobile *character;
                Mobile *target;
                double maxForce;
                double separationRadius;

                BoundedDynamicSeparation(std::string name, Mobile *character, Mobile *target, double maxForce, double separationRadius);

                virtual std::vector<Triple> getForce(unsigned int ticks, unsigned int delta_ticks);
};

#endif

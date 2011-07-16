#ifndef DYNAMICSEPARATION_HPP
#define DYNAMICSEPARATION_HPP

#include <vector>

#include "DynamicV.hpp"
#include "Triple.hpp"

class Mobile;

class DynamicSeparation : public virtual DynamicV {
        public:
                Mobile *character;
                Mobile *target;
                double minForce;
                double separationRadius;

                DynamicSeparation(std::string name, Mobile *character, Mobile *target, double minForce, double separationRadius);

                virtual std::vector<Triple> getForce(unsigned int ticks, unsigned int delta_ticks);
};

#endif

#ifndef DYNAMICA_HPP
#define DYNAMICA_HPP

#include <vector>

#include "Behavior.hpp"
#include "Triple.hpp"

#define DynamicA_CALL_NAME getTorque

class DynamicA : public virtual Behavior {
        public:
                DynamicA(std::string name);

                virtual std::vector<double> DynamicA_CALL_NAME(unsigned int ticks, unsigned int delta_ticks) = 0;
};

#endif

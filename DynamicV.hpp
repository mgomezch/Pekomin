#ifndef DYNAMICV_HPP
#define DYNAMICV_HPP

#include <vector>

#include "Behavior.hpp"
#include "Triple.hpp"

#define DynamicV_CALL_NAME getForce

class DynamicV : public virtual Behavior {
        public:
                DynamicV(std::string name);

                virtual std::vector<Triple> DynamicV_CALL_NAME(unsigned int ticks, unsigned int delta_ticks) = 0;
};

#endif

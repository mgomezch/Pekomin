#ifndef _DYNAMICV_HPP
#define _DYNAMICV_HPP

#include <utility>

#include "Behavior.hpp"
#include "Triple.hpp"

using namespace std;

class DynamicV : public virtual Behavior {
        public:
                virtual pair<bool, Triple> getForce(unsigned int ticks) = 0;
};

#endif

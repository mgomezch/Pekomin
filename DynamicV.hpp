#ifndef DYNAMICV_HPP
#define DYNAMICV_HPP

#include <utility>

#include "Behavior.hpp"
#include "Triple.hpp"

using namespace std;

#define DynamicV_CALL_NAME getForce

class DynamicV : public virtual Behavior {
        public:
                DynamicV(string name);

                virtual pair<bool, Triple> DynamicV_CALL_NAME(unsigned int ticks) = 0;
};

#endif

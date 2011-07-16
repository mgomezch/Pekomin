#ifndef DYNAMICV_HPP
#define DYNAMICV_HPP

#include <vector>

#include "Behavior.hpp"
#include "Triple.hpp"

using namespace std;

#define DynamicV_CALL_NAME getForce

class DynamicV : public virtual Behavior {
        public:
                DynamicV(string name);

                virtual vector<Triple> DynamicV_CALL_NAME(unsigned int ticks) = 0;
};

#endif

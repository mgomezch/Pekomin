#ifndef DYNAMICA_HPP
#define DYNAMICA_HPP

#include <utility>

#include "Behavior.hpp"
#include "Triple.hpp"

using namespace std;

#define DynamicA_CALL_NAME getTorque

class DynamicA : public virtual Behavior {
        public:
                virtual pair<bool, double> DynamicA_CALL_NAME(unsigned int ticks) = 0;
};

#endif

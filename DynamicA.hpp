#ifndef _DYNAMICA_HPP
#define _DYNAMICA_HPP

#include <utility>

#include "Behavior.hpp"
#include "Triple.hpp"

using namespace std;

class DynamicA : public Behavior {
        public:
                virtual pair<bool, double> getTorque(unsigned int ticks) = 0;
};

#endif

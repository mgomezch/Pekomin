#ifndef _DYNAMIC_HPP
#define _DYNAMIC_HPP

#include <tuple>

#include "Behavior.hpp"
#include "Triple.hpp"

using namespace std;

class Dynamic : public Behavior {
        public:
                virtual tuple<bool, Triple, double> getForce(unsigned int ticks) = 0;
};

#endif

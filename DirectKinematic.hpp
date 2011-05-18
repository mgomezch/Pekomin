#ifndef _DIRECTKINEMATIC_HPP
#define _DIRECTKINEMATIC_HPP

#include <tuple>

#include "Behavior.hpp"
#include "Triple.hpp"

using namespace std;

class DirectKinematic : public Behavior {
        public:
                virtual tuple<bool, Triple, double> getVel(unsigned int ticks) = 0;
};

#endif

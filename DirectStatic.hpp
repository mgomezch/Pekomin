#ifndef _DIRECTSTATIC_HPP
#define _DIRECTSTATIC_HPP

#include <tuple>

#include "Behavior.hpp"
#include "Triple.hpp"

using namespace std;

class DirectStatic : public Behavior {
        public:
                virtual tuple<bool, Triple, double> getPos(unsigned int ticks) = 0;
};

#endif

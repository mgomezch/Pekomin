#ifndef _KINEMATIC_HPP
#define _KINEMATIC_HPP

#include <tuple>

#include "Behavior.hpp"
#include "Triple.hpp"

using namespace std;

class Kinematic : public Behavior {
        public:
                virtual tuple<bool, Triple, double> getVelIncr(unsigned int ticks) = 0;
};

#endif

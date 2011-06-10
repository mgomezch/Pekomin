#ifndef _KINEMATICV_HPP
#define _KINEMATICV_HPP

#include <utility>

#include "Behavior.hpp"
#include "Triple.hpp"

using namespace std;

class KinematicV : public Behavior {
        public:
                virtual pair<bool, Triple> getVelIncr(unsigned int ticks) = 0;
};

#endif

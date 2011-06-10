#ifndef _DIRECTKINEMATICV_HPP
#define _DIRECTKINEMATICV_HPP

#include <utility>

#include "Behavior.hpp"
#include "Triple.hpp"

using namespace std;

class DirectKinematicV : public Behavior {
        public:
                virtual pair<bool, Triple> getVel(unsigned int ticks) = 0;
};

#endif

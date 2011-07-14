#ifndef DIRECTKINEMATICV_HPP
#define DIRECTKINEMATICV_HPP

#include <utility>

#include "Behavior.hpp"
#include "Triple.hpp"

using namespace std;

#define DirectKinematicV_CALL_NAME getVel

class DirectKinematicV : public virtual Behavior {
        public:
                virtual pair<bool, Triple> DirectKinematicV_CALL_NAME(unsigned int ticks) = 0;
};

#endif

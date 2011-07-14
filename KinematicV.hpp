#ifndef KINEMATICV_HPP
#define KINEMATICV_HPP

#include <utility>

#include "Behavior.hpp"
#include "Triple.hpp"

using namespace std;

#define KinematicV_CALL_NAME getVelIncr

class KinematicV : public virtual Behavior {
        public:
                virtual pair<bool, Triple> KinematicV_CALL_NAME(unsigned int ticks) = 0;
};

#endif

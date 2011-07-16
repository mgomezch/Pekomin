#ifndef KINEMATICV_HPP
#define KINEMATICV_HPP

#include <vector>

#include "Behavior.hpp"
#include "Triple.hpp"

#define KinematicV_CALL_NAME getVelIncr

class KinematicV : public virtual Behavior {
        public:
                KinematicV(std::string name);

                virtual std::vector<Triple> KinematicV_CALL_NAME(unsigned int ticks, unsigned int delta_ticks) = 0;
};

#endif

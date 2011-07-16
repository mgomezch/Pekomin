#ifndef DIRECTKINEMATICV_HPP
#define DIRECTKINEMATICV_HPP

#include <vector>

#include "Behavior.hpp"
#include "Triple.hpp"

#define DirectKinematicV_CALL_NAME getVel

class DirectKinematicV : public virtual Behavior {
        public:
                DirectKinematicV(std::string name);

                virtual std::vector<Triple> DirectKinematicV_CALL_NAME(unsigned int ticks, unsigned int delta_ticks) = 0;
};

#endif

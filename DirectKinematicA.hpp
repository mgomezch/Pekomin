#ifndef DIRECTKINEMATICA_HPP
#define DIRECTKINEMATICA_HPP

#include <vector>

#include "Behavior.hpp"
#include "Triple.hpp"

#define DirectKinematicA_CALL_NAME getAngVel

class DirectKinematicA : public virtual Behavior {
        public:
                DirectKinematicA(std::string name);

                virtual std::vector<double> DirectKinematicA_CALL_NAME(unsigned int ticks, unsigned int delta_ticks) = 0;
};

#endif

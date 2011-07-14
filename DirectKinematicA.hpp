#ifndef DIRECTKINEMATICA_HPP
#define DIRECTKINEMATICA_HPP

#include <utility>

#include "Behavior.hpp"
#include "Triple.hpp"

using namespace std;

#define DirectKinematicA_CALL_NAME getAngVel

class DirectKinematicA : public virtual Behavior {
        public:
                virtual pair<bool, double> DirectKinematicA_CALL_NAME(unsigned int ticks) = 0;
};

#endif

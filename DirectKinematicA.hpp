#ifndef _DIRECTKINEMATICA_HPP
#define _DIRECTKINEMATICA_HPP

#include <utility>

#include "Behavior.hpp"
#include "Triple.hpp"

using namespace std;

class DirectKinematicA : public Behavior {
        public:
                virtual pair<bool, double> getAngVel(unsigned int ticks) = 0;
};

#endif

#ifndef _KINEMATICA_HPP
#define _KINEMATICA_HPP

#include <utility>

#include "Behavior.hpp"
#include "Triple.hpp"

using namespace std;

class KinematicA : public Behavior {
        public:
                virtual pair<bool, double> getAngVelIncr(unsigned int ticks) = 0;
};

#endif

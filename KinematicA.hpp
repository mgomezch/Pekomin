#ifndef KINEMATICA_HPP
#define KINEMATICA_HPP

#include <utility>

#include "Behavior.hpp"

using namespace std;

#define KinematicA_CALL_NAME getAngVelIncr

class KinematicA : public virtual Behavior {
        public:
                virtual pair<bool, double> KinematicA_CALL_NAME(unsigned int ticks) = 0;
};

#endif

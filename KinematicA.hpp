#ifndef KINEMATICA_HPP
#define KINEMATICA_HPP

#include <vector>

#include "Behavior.hpp"

using namespace std;

#define KinematicA_CALL_NAME getAngVelIncr

class KinematicA : public virtual Behavior {
        public:
                KinematicA(string name);
                virtual vector<double> KinematicA_CALL_NAME(unsigned int ticks) = 0;
};

#endif

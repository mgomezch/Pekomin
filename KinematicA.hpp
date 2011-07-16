#ifndef KINEMATICA_HPP
#define KINEMATICA_HPP

#include <vector>

#include "Behavior.hpp"

#define KinematicA_CALL_NAME getAngVelIncr

class KinematicA : public virtual Behavior {
        public:
                KinematicA(std::string name);
                virtual std::vector<double> KinematicA_CALL_NAME(unsigned int ticks, unsigned int delta_ticks) = 0;
};

#endif

#ifndef KINEMATICV_HPP
#define KINEMATICV_HPP

#include <vector>

#include "Behavior.hpp"
#include "Triple.hpp"

using namespace std;

#define KinematicV_CALL_NAME getVelIncr

class KinematicV : public virtual Behavior {
        public:
                KinematicV(string name);

                virtual vector<Triple> KinematicV_CALL_NAME(unsigned int ticks) = 0;
};

#endif

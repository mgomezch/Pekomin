#ifndef _KINEMATIC_HPP
#define _KINEMATIC_HPP

#include <tuple>

#include "Behavior.hpp"

using namespace std;

class Kinematic : public Behavior {
        public:
                static const unsigned int family = BEHAVIOR_FAMILY_KINEMATIC;

                virtual tuple<bool, Triple, double> getVelIncr() = 0;
};

#endif

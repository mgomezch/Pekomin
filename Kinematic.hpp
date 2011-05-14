#ifndef _KINEMATIC_HPP
#define _KINEMATIC_HPP

#include <tuple>

#include "Behavior.hpp"

using namespace std;

class Kinematic : public Behavior {
        public:
                virtual unsigned int family();
                virtual tuple<bool, Triple, double> getVelIncr() = 0;
};

#endif

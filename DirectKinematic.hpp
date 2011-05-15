#ifndef _DIRECTKINEMATIC_HPP
#define _DIRECTKINEMATIC_HPP

#include <tuple>

#include "Behavior.hpp"

using namespace std;

class DirectKinematic : public Behavior {
        public:
                virtual unsigned int family();
                virtual tuple<bool, Triple, double> getVel() = 0;
};

#endif

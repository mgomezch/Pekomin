#ifndef _STATIC_HPP
#define _STATIC_HPP

#include <tuple>

#include "Behavior.hpp"

using namespace std;

class Static : public Behavior {
        public:
                static const unsigned int family = BEHAVIOR_FAMILY_STATIC;

                virtual tuple<bool, Triple, double> getPosIncr() = 0;
};

#endif

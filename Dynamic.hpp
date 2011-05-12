#ifndef _DYNAMIC_HPP
#define _DYNAMIC_HPP

#include <tuple>

#include "Behavior.hpp"

using namespace std;

class Dynamic : public Behavior {
        public:
                static const unsigned int family = BEHAVIOR_FAMILY_DYNAMIC;

                virtual tuple<bool, Triple, double> getForceIncr() = 0;
};

#endif

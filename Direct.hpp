#ifndef _DIRECT_HPP
#define _DIRECT_HPP

#include <tuple>

#include "Behavior.hpp"

using namespace std;

class Direct : public Behavior {
        public:
                static const unsigned int family = BEHAVIOR_FAMILY_DIRECT;

                virtual tuple<bool, Triple, double> getPos() = 0;
};

#endif

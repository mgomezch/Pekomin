#ifndef _STATIC_HPP
#define _STATIC_HPP

#include "Behavior.hpp"

using namespace std;

class Static : Behavior {
        public:
                static const unsigned int family = BEHAVIOR_FAMILY_STATIC;
};

#endif

#ifndef _BEHAVIOR_HPP
#define _BEHAVIOR_HPP

#include <stdio.h>

#include <cmath>
#include <iostream>
#include <string>

#include "Triple.hpp"

using namespace std;

enum behavior_families {
        BEHAVIOR_FAMILY_INVALID = 0,
        BEHAVIOR_FAMILY_DIRECTSTATIC = 1,
        BEHAVIOR_FAMILY_STATIC = 2,
        BEHAVIOR_FAMILY_DIRECTKINEMATIC = 4,
        BEHAVIOR_FAMILY_KINEMATIC = 8,
        BEHAVIOR_FAMILY_DYNAMIC = 16
};

enum behaviors {
        BEHAVIOR_INVALID = 0,
        BEHAVIOR_ALIGN,
        BEHAVIOR_ARRIVE,
        BEHAVIOR_EVADE,
        BEHAVIOR_FACE,
        BEHAVIOR_FLEE,
        BEHAVIOR_LOOKWHEREYOUREGOING,
        BEHAVIOR_PURSUE,
        BEHAVIOR_SEEK,
        BEHAVIOR_SEPARATION,
        BEHAVIOR_VELOCITYMATCH,
        BEHAVIOR_WANDER,
        BEHAVIOR_KINEMATICARRIVE,
        BEHAVIOR_KINEMATICFLEE,
        BEHAVIOR_KINEMATICSEEK,
        BEHAVIOR_KINEMATICWANDER
};

class Behavior {
        public:
                virtual unsigned int family() = 0;
                virtual unsigned int type() = 0;
};

#endif

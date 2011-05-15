#ifndef _BEHAVIOR_HPP
#define _BEHAVIOR_HPP

using namespace std;

/*
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
*/

class Behavior {
        public:
                virtual ~Behavior() = 0;
//              virtual unsigned int type() = 0;
};

inline Behavior::~Behavior() {}

#endif

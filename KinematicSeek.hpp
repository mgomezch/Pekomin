#ifndef _KINEMATICSEEK_HPP
#define _KINEMATICSEEK_HPP

#include "Kinematic.hpp"

using namespace std;

class Ent;

class KinematicSeek : public Kinematic {
        public:
                static const unsigned int type = BEHAVIOR_KINEMATICSEEK;
                Ent *character;
                Ent *target;
                double maxSpeed;

                KinematicSeek(Ent *character, Ent *target, double maxSpeed);
};

#endif

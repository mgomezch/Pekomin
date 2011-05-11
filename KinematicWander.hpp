#ifndef _KINEMATICWANDER_HPP
#define _KINEMATICWANDER_HPP

#include "Kinematic.hpp"

class Ent;

class KinematicWander : Kinematic {
        public:
                static const unsigned int type = BEHAVIOR_KINEMATICWANDER;
                Ent *character;
                double maxSpeed;
                double maxRotation;

                KinematicWander(Ent *character, double maxSpeed, double maxRotation);
                pair<Triple, double> getSteering();
};

#endif

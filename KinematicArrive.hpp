#ifndef _KINEMATICARRIVE_HPP
#define _KINEMATICARRIVE_HPP

#include "Kinematic.hpp"

using namespace std;

class Ent;

class KinematicArrive : Kinematic {
        public:
                static const unsigned int type = BEHAVIOR_KINEMATICARRIVE;
                Ent *character;
                Ent *target;
                double maxSpeed;
                double radius;
                static const double timeToTarget = 0.25;

                KinematicArrive(Ent *character, Ent *target, double maxSpeed, double radius);
                pair<Triple, double> getSteering();
};

#endif

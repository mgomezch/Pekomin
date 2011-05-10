#ifndef _KINEMATICARRIVE_HPP
#define _KINEMATICARRIVE_HPP

#include "Kinematic.hpp"
#include "Ent.hpp"

using namespace std;

class KinematicArrive: Kinematic {
        public:
                Ent *character;
                Ent *target;
                double maxSpeed;
                double radius;
                static const double timeToTarget = 0.25;

                KinematicArrive(Ent *character, Ent *target, double maxSpeed, double radius);
                pair<Triple, double> getSteering();
};

#endif

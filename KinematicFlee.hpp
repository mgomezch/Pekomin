#ifndef _KINEMATICFLEE_HPP
#define _KINEMATICFLEE_HPP

#include "Behavior.hpp"

using namespace std;

class KinematicFlee: Kinematic {
        public:
                Ent *character;
                Ent *target;
                double maxSpeed;

                KinematicFlee(Ent *character, Ent *target, double maxSpeed);
                pair<Triple, double> getSteering();
                string name();
};

#endif

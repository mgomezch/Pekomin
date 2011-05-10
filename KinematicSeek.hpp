#ifndef _KINEMATICSEEK_HPP
#define _KINEMATICSEEK_HPP

#include "Behavior.hpp"

using namespace std;

class KinematicSeek: Kinematic {
        public:
                Ent *character;
                Ent *target;
                double maxSpeed;

                KinematicSeek(Ent *character, Ent *target, double maxSpeed);
                pair<Triple,double> getSteering();
                string name();
};

#endif

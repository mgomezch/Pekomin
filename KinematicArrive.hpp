#ifndef _KINEMATICARRIVE_HPP
#define _KINEMATICARRIVE_HPP

#include "Kinematic.hpp"

using namespace std;

class Ent;

class KinematicArrive : public Kinematic {
        public:
                Ent *character;
                Ent *target;
                double maxSpeed;
                double radius;
                static const double timeToTarget = 0.25;

                KinematicArrive(Ent *character, Ent *target, double maxSpeed, double radius);
//              virtual unsigned int type();

                virtual tuple<bool, Triple, double> getVelIncr();
};

#endif

#ifndef _KINEMATICFLEE_HPP
#define _KINEMATICFLEE_HPP

#include "Kinematic.hpp"

using namespace std;

class Ent;

class KinematicFlee : public Kinematic {
        public:
                Ent *character;
                Ent *target;
                double maxSpeed;

                KinematicFlee(Ent *character, Ent *target, double maxSpeed);

                virtual tuple<bool, Triple, double> getVelIncr(unsigned int ticks);
};

#endif

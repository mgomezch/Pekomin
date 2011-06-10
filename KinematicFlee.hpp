#ifndef _KINEMATICFLEE_HPP
#define _KINEMATICFLEE_HPP

#include "KinematicV.hpp"

using namespace std;

class Ent;

class KinematicFlee : public KinematicV {
        public:
                Ent *character;
                Ent *target;
                double maxSpeed;

                KinematicFlee(Ent *character, Ent *target, double maxSpeed);

                virtual pair<bool, Triple> getVelIncr(unsigned int ticks);
};

#endif

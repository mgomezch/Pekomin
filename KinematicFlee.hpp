#ifndef _KINEMATICFLEE_HPP
#define _KINEMATICFLEE_HPP

#include "KinematicV.hpp"
#include "Triple.hpp"

using namespace std;

class Ent;

class KinematicFlee : public KinematicV {
        public:
                Ent *character;
                Ent *target;
                double maxSpeed;
                double fleeRadius;

                KinematicFlee(Ent *character, Ent *target, double maxSpeed, double fleeRadius);

                virtual pair<bool, Triple> getVelIncr(unsigned int ticks);
};

#endif

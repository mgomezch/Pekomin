#ifndef _KINEMATICFLEE_HPP
#define _KINEMATICFLEE_HPP

#include "DirectKinematicV.hpp"

using namespace std;

class Ent;

class KinematicFlee : public DirectKinematicV {
        public:
                Ent *character;
                Ent *target;
                double maxSpeed;
		double fleeRadius;

                KinematicFlee(Ent *character, Ent *target, double maxSpeed, double fleeRadius);

                virtual pair<bool, Triple> getVel(unsigned int ticks);
};

#endif

#ifndef _KINEMATICWANDER_HPP
#define _KINEMATICWANDER_HPP

#include "DirectKinematicV.hpp"

class Ent;

class KinematicWander : public DirectKinematicV {
        public:
                Ent *character;
                double maxSpeed;
                double maxRotation;
                int accum;

                KinematicWander(Ent *character, double maxSpeed, double maxRotation);

                virtual pair<bool, Triple> getVel(unsigned int ticks);
};

#endif

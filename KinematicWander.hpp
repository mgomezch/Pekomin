#ifndef _KINEMATICWANDER_HPP
#define _KINEMATICWANDER_HPP

#include "KinematicV.hpp"

class Ent;

class KinematicWander : public KinematicV {
        public:
                Ent *character;
                double maxSpeed;
                double maxRotation;
                int accum;

                KinematicWander(Ent *character, double maxSpeed, double maxRotation);

                virtual pair<bool, Triple> getVelIncr(unsigned int ticks);
};

#endif

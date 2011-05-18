#ifndef _KINEMATICWANDER_HPP
#define _KINEMATICWANDER_HPP

#include "Kinematic.hpp"

class Ent;

class KinematicWander : public Kinematic {
        public:
                Ent *character;
                double maxSpeed;
                double maxRotation;
                int accum;

                KinematicWander(Ent *character, double maxSpeed, double maxRotation);

                virtual tuple<bool, Triple, double> getVelIncr(unsigned int ticks);
};

#endif

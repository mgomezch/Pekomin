#ifndef _KINEMATICWANDER_HPP
#define _KINEMATICWANDER_HPP

#include "Kinematic.hpp"

class Ent;

class KinematicWander : public Kinematic {
        public:
                Ent *character;
                double maxSpeed;
                double maxRotation;

                KinematicWander(Ent *character, double maxSpeed, double maxRotation);
                virtual unsigned int type();

                virtual tuple<bool, Triple, double> getVelIncr();
};

#endif

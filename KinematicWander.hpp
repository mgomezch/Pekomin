#ifndef KINEMATICWANDER_HPP
#define KINEMATICWANDER_HPP

#include "DirectKinematicV.hpp"
#include "Triple.hpp"

class Ent;

class KinematicWander : public virtual DirectKinematicV {
        public:
                Ent *character;
                double maxSpeed;
                double maxRotation;
                double wanderTime;

                int accum;

                KinematicWander(string name, Ent *character, double maxSpeed, double maxRotation, double wanderTime);

                virtual vector<Triple> getVel(unsigned int ticks);
};

#endif

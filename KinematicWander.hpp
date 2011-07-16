#ifndef KINEMATICWANDER_HPP
#define KINEMATICWANDER_HPP

#include <vector>

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

                KinematicWander(std::string name, Ent *character, double maxSpeed, double maxRotation, double wanderTime);

                virtual std::vector<Triple> getVel(unsigned int ticks, unsigned int delta_ticks);
};

#endif

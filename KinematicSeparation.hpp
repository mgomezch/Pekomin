#ifndef KINEMATICSEPARATION_HPP
#define KINEMATICSEPARATION_HPP

#include <vector>

#include "KinematicV.hpp"
#include "Triple.hpp"

class Ent;

class KinematicSeparation : public virtual KinematicV {
        public:
                Ent *character;
                Ent *target;
                double maxSpeed;
                double separationRadius;

                KinematicSeparation(std::string name, Ent *character, Ent *target, double maxSpeed, double separationRadius);

                virtual std::vector<Triple> getVelIncr(unsigned int ticks, unsigned int delta_ticks);
};

#endif

#ifndef KINEMATICSEPARATION_HPP
#define KINEMATICSEPARATION_HPP

#include "KinematicV.hpp"
#include "Triple.hpp"

using namespace std;

class Ent;

class KinematicSeparation : public virtual KinematicV {
        public:
                Ent *character;
                Ent *target;
                double maxSpeed;
                double separationRadius;

                KinematicSeparation(string name, Ent *character, Ent *target, double maxSpeed, double separationRadius);

                virtual vector<Triple> getVelIncr(unsigned int ticks);
};

#endif

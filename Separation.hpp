#ifndef SEPARATION_HPP
#define SEPARATION_HPP

#include "KinematicV.hpp"
#include "Triple.hpp"

using namespace std;

class Mobile;

class Separation : public virtual KinematicV {
        public:
                Mobile *character;
                Mobile *target;
                double maxSpeed;
                double separationRadius;

                Separation(string name, Mobile *character, Mobile *target, double maxSpeed, double separationRadius);

                virtual vector<Triple> getVelIncr(unsigned int ticks);
};

#endif

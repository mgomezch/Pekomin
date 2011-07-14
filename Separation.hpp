#ifndef SEPARATION_HPP
#define SEPARATION_HPP

#include "KinematicV.hpp"
#include "Triple.hpp"

using namespace std;

class Mobile;

class Separation : public KinematicV {
        public:
                Mobile *character;
                Mobile *target;
                double maxSpeed;
                double separationRadius;

                Separation(Mobile *character, Mobile *target, double maxSpeed, double separationRadius);

                virtual pair<bool, Triple> getVelIncr(unsigned int ticks);
};

#endif

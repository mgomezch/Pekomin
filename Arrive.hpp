#ifndef _ARRIVE_HPP
#define _ARRIVE_HPP

#include "KinematicV.hpp"

using namespace std;

class Mobile;

class Arrive : public KinematicV {
        public:
                Mobile *character;
                Mobile *target;
                double maxSpeed;
                double targetRadius;
                double slowRadius;

                Arrive(Mobile *character, Mobile *target, double maxSpeed, double targetRadius, double slowRadius);

                virtual pair<bool, Triple> getVelIncr(unsigned int ticks);
};

#endif

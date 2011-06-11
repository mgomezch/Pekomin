#ifndef _ARRIVE_HPP
#define _ARRIVE_HPP

#include "DirectKinematicV.hpp"

using namespace std;

class Mobile;

class Arrive : public DirectKinematicV {
        public:
                Mobile *character;
                Mobile *target;
                double maxSpeed;
                double targetRadius;
                double slowRadius;

                Arrive(Mobile *character, Mobile *target, double maxSpeed, double targetRadius, double slowRadius);

                virtual pair<bool, Triple> getVel(unsigned int ticks);
};

#endif

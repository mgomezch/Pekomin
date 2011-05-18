#ifndef _ARRIVE_HPP
#define _ARRIVE_HPP

#include "Kinematic.hpp"

using namespace std;

class Mobile;

class Arrive : public Kinematic {
        public:
                Mobile *character;
                Mobile *target;
                double maxSpeed;
                double targetRadius;
                double slowRadius;

                Arrive(Mobile *character, Mobile *target, double maxSpeed, double targetRadius, double slowRadius);

                virtual tuple<bool, Triple, double> getVelIncr(unsigned int ticks);
};

#endif

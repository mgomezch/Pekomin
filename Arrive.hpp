#ifndef ARRIVE_HPP
#define ARRIVE_HPP

#include "DirectKinematicV.hpp"

using namespace std;

class Mobile;

class Arrive : public virtual DirectKinematicV {
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

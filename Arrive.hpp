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

                Arrive(string name, Mobile *character, Mobile *target, double maxSpeed, double targetRadius, double slowRadius);

                virtual vector<Triple> getVel(unsigned int ticks);
};

#endif

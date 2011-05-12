#ifndef _ARRIVE_HPP
#define _ARRIVE_HPP

#include "Kinematic.hpp"

using namespace std;

class Mobile;

class Arrive : public Kinematic {
        public:
                static const unsigned int type = BEHAVIOR_ARRIVE;
                Mobile *character;
                Mobile *target;
                double maxAcceleration;
                double maxSpeed;
                double targetRadius;
                double slowRadius;
                static const double timeToTarget = 0.1;

                Arrive(Mobile *character, Mobile *target, double maxAcceleration, double maxSpeed, double targetRadius, double slowRadius);
                virtual tuple<bool, Triple, double> getVelIncr();
};

#endif

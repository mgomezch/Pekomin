#ifndef LOOKWHEREYOUREGOING_HPP
#define LOOKWHEREYOUREGOING_HPP

#include "DirectKinematicA.hpp"

using namespace std;

class Mobile;

class LookWhereYoureGoing : public virtual DirectKinematicA {
        public:
                Mobile *character;
                double maxAngularVelocity;
                double targetRadius;
                double slowRadius;

                LookWhereYoureGoing(string name, Mobile *character, double maxAngularVelocity, double targetRadius, double slowRadius);

                virtual vector<double> getAngVel(unsigned int ticks);
};

#endif

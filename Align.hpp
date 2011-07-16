#ifndef ALIGN_HPP
#define ALIGN_HPP

#include "DirectKinematicA.hpp"

using namespace std;

class Mobile;

class Align : public virtual DirectKinematicA {
        public:
                Mobile *character;
                Mobile *target;
                double maxAngularVelocity;
                double targetRadius;
                double slowRadius;

                Align(string name, Mobile *character, Mobile *target, double maxAngularVelocity, double targetRadius, double slowRadius);

                virtual vector<double> getAngVel(unsigned int ticks);
};

#endif

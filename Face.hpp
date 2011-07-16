#ifndef FACE_HPP
#define FACE_HPP

#include "KinematicA.hpp"

using namespace std;

class Mobile;

class Face : public virtual KinematicA {
        public:
                Mobile *character;
                Mobile *target;
                double maxAngularVelocity;
                double targetRadius;
                double slowRadius;

                Face(string name, Mobile *character, Mobile *target, double maxAngularVelocity, double targetRadius, double slowRadius);

                virtual vector<double> getAngVelIncr(unsigned int ticks);
};

#endif

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

                Face(Mobile *character, Mobile *target, double maxAngularVelocity, double targetRadius, double slowRadius);

                virtual pair<bool, double> getAngVelIncr(unsigned int ticks);
};

#endif

#ifndef FACE_HPP
#define FACE_HPP

#include <vector>

#include "KinematicA.hpp"

class Mobile;

class Face : public virtual KinematicA {
        public:
                Mobile *character;
                Mobile *target;
                double maxAngularVelocity;
                double targetRadius;
                double slowRadius;

                Face(std::string name, Mobile *character, Mobile *target, double maxAngularVelocity, double targetRadius, double slowRadius);

                virtual std::vector<double> getAngVelIncr(unsigned int ticks, unsigned int delta_ticks);
};

#endif

#ifndef ALIGN_HPP
#define ALIGN_HPP

#include <vector>

#include "DirectKinematicA.hpp"

class Mobile;

class Align : public virtual DirectKinematicA {
        public:
                Mobile *character;
                Mobile *target;
                double maxAngularVelocity;
                double targetRadius;
                double slowRadius;

                Align(std::string name, Mobile *character, Mobile *target, double maxAngularVelocity, double targetRadius, double slowRadius);

                virtual std::vector<double> getAngVel(unsigned int ticks, unsigned int delta_ticks);
};

#endif

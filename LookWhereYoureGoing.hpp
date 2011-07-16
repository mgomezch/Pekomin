#ifndef LOOKWHEREYOUREGOING_HPP
#define LOOKWHEREYOUREGOING_HPP

#include <vector>

#include "DirectKinematicA.hpp"

class Mobile;

class LookWhereYoureGoing : public virtual DirectKinematicA {
        public:
                Mobile *character;
                double maxAngularVelocity;
                double targetRadius;
                double slowRadius;

                LookWhereYoureGoing(std::string name, Mobile *character, double maxAngularVelocity, double targetRadius, double slowRadius);

                virtual std::vector<double> getAngVel(unsigned int ticks, unsigned int delta_ticks);
};

#endif

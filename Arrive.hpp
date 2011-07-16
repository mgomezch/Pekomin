#ifndef ARRIVE_HPP
#define ARRIVE_HPP

#include <vector>

#include "DirectKinematicV.hpp"

class Mobile;

class Arrive : public virtual DirectKinematicV {
        public:
                Mobile *character;
                Mobile *target;
                double maxSpeed;
                double targetRadius;
                double slowRadius;

                Arrive(std::string name, Mobile *character, Mobile *target, double maxSpeed, double targetRadius, double slowRadius);

                virtual std::vector<Triple> getVel(unsigned int ticks, unsigned int delta_ticks);
};

#endif

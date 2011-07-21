#ifndef SMELL_HPP
#define SMELL_HPP

#include <vector>

#include "DirectKinematicV.hpp"
#include "Triple.hpp"

class Mobile;

class Smell : public virtual DirectKinematicV {
        public:
                Mobile *character;
                double maxSpeed;
                double range;

                Smell(std::string name, Mobile *character, double maxSpeed, double range);

                virtual std::vector<Triple> getVel(unsigned int ticks, unsigned int delta_ticks);
};

#endif

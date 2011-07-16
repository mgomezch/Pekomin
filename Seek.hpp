#ifndef SEEK_HPP
#define SEEK_HPP

#include <vector>

#include "DirectKinematicV.hpp"
#include "Triple.hpp"

class Mobile;

class Seek : public virtual DirectKinematicV {
        public:
                Mobile *character;
                Mobile *target;
                double maxSpeed;

                Seek(std::string name, Mobile *character, Mobile *target, double maxSpeed);

                virtual std::vector<Triple> getVel(unsigned int ticks, unsigned int delta_ticks);
};

#endif

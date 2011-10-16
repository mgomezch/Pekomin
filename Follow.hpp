#ifndef FOLLOW_HPP
#define FOLLOW_HPP

#include <vector>

#include "DirectKinematicV.hpp"
#include "Phantom.hpp"
#include "Triple.hpp"

class Mobile;
class Arrive;

class Follow : public virtual DirectKinematicV {
        public:
                Mobile *character;
                Mobile *target;
                Phantom marcus; // TODO: change name
                double phantomOffset;

                Arrive *arrive;

                Follow(std::string name, Mobile *character, Mobile *target, double phantomOffset, double maxSpeed, double targetRadius, double slowRadius);

                virtual ~Follow();

                virtual std::vector<Triple> getVel(unsigned int ticks, unsigned int delta_ticks);
};

#endif

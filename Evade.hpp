#ifndef EVADE_HPP
#define EVADE_HPP

#include <vector>

#include "DirectKinematicV.hpp"
#include "Triple.hpp"

class Mobile;

class Evade : public virtual DirectKinematicV {
        public:
                Mobile *character;
                Mobile *target;
                double maxSpeed;

                static const double maxPrediction = 10;

                Evade(std::string name, Mobile *character, Mobile *target, double maxSpeed);

                virtual std::vector<Triple> getVel(unsigned int ticks, unsigned int delta_ticks);
};

#endif

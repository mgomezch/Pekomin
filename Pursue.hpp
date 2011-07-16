#ifndef PURSUE_HPP
#define PURSUE_HPP

#include <vector>

#include "DirectKinematicV.hpp"
#include "Triple.hpp"

class Mobile;

class Pursue : public virtual DirectKinematicV {
        public:
                Mobile *character;
                Mobile *target;
                double maxSpeed;

                static const double maxPrediction = 10;

                Pursue(std::string name, Mobile *character, Mobile *target, double maxSpeed);

                virtual std::vector<Triple> getVel(unsigned int ticks, unsigned int delta_ticks);
};

#endif

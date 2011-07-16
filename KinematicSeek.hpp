#ifndef KINEMATICSEEK_HPP
#define KINEMATICSEEK_HPP

#include <vector>

#include "KinematicV.hpp"
#include "Triple.hpp"

class Ent;

class KinematicSeek : public virtual KinematicV {
        public:
                Ent *character;
                Ent *target;
                double maxSpeed;

                KinematicSeek(std::string name, Ent *character, Ent *target, double maxSpeed);

                virtual std::vector<Triple> getVelIncr(unsigned int ticks, unsigned int delta_ticks);
};

#endif

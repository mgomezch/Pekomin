#ifndef KINEMATICSEEK_HPP
#define KINEMATICSEEK_HPP

#include "KinematicV.hpp"
#include "Triple.hpp"

using namespace std;

class Ent;

class KinematicSeek : public virtual KinematicV {
        public:
                Ent *character;
                Ent *target;
                double maxSpeed;

                KinematicSeek(Ent *character, Ent *target, double maxSpeed);

                virtual pair<bool, Triple> getVelIncr(unsigned int ticks);
};

#endif

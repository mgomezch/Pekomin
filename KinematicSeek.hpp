#ifndef _KINEMATICSEEK_HPP
#define _KINEMATICSEEK_HPP

#include "DirectKinematicV.hpp"

using namespace std;

class Ent;

class KinematicSeek : public DirectKinematicV {
        public:
                Ent *character;
                Ent *target;
                double maxSpeed;

                KinematicSeek(Ent *character, Ent *target, double maxSpeed);

                virtual pair<bool, Triple> getVel(unsigned int ticks);
};

#endif

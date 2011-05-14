#ifndef _KINEMATICSEEK_HPP
#define _KINEMATICSEEK_HPP

#include "Kinematic.hpp"

using namespace std;

class Ent;

class KinematicSeek : public Kinematic {
        public:
                Ent *character;
                Ent *target;
                double maxSpeed;

                KinematicSeek(Ent *character, Ent *target, double maxSpeed);
                virtual unsigned int type();

                virtual tuple<bool, Triple, double> getVelIncr();
};

#endif

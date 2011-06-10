#ifndef _SEEK_HPP
#define _SEEK_HPP

#include "KinematicV.hpp"

using namespace std;

class Mobile;

class Seek : public KinematicV {
        public:
                Mobile *character;
                Mobile *target;
                double maxAcceleration;

                Seek(Mobile *character, Mobile *target, double maxAcceleration);

                virtual pair<bool, Triple> getVelIncr(unsigned int ticks);
};

#endif

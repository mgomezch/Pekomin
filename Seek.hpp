#ifndef _SEEK_HPP
#define _SEEK_HPP

#include "DirectKinematicV.hpp"

using namespace std;

class Mobile;

class Seek : public DirectKinematicV {
        public:
                Mobile *character;
                Mobile *target;
                double maxSpeed;

                Seek(Mobile *character, Mobile *target, double maxSpeed);

                virtual pair<bool, Triple> getVel(unsigned int ticks);
};

#endif

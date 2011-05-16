#ifndef _SEEK_HPP
#define _SEEK_HPP

#include "Kinematic.hpp"

using namespace std;

class Mobile;

class Seek : public Kinematic {
        public:
                Mobile *character;
                Mobile *target;
                double maxAcceleration;

                Seek(Mobile *character, Mobile *target, double maxAcceleration);
//              virtual unsigned int type();

                virtual tuple<bool, Triple, double> getVelIncr();
};

#endif

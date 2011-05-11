#ifndef _SEEK_HPP
#define _SEEK_HPP

#include "Behavior.hpp"

using namespace std;

class Mobile;

class Seek : Behavior {
        public:
                static const unsigned int type = BEHAVIOR_SEEK;
                Mobile *character;
                Mobile *target;
                double maxAcceleration;

                Seek() {}
                Seek(Mobile *character, Mobile *target, double maxAcceleration);

                pair<Triple, double> getSteering();
};

#endif

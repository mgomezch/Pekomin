#ifndef SEEK_HPP
#define SEEK_HPP

#include "DirectKinematicV.hpp"
#include "Triple.hpp"

using namespace std;

class Mobile;

class Seek : public virtual DirectKinematicV {
        public:
                Mobile *character;
                Mobile *target;
                double maxSpeed;

                Seek(string name, Mobile *character, Mobile *target, double maxSpeed);

                virtual vector<Triple> getVel(unsigned int ticks);
};

#endif

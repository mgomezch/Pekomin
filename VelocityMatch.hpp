#ifndef _VELOCITYMATCH_HPP
#define _VELOCITYMATCH_HPP

#include "DirectKinematic.hpp"

using namespace std;

class Mobile;

class VelocityMatch : public DirectKinematic {
        public:
                Mobile *character;
                Mobile *target;
                double maxAcceleration;
                static const double timeToTarget = 0.1;

                VelocityMatch(Mobile *character, Mobile *target, double maxAcceleration);
//              virtual unsigned int type();

                virtual tuple<bool, Triple, double> getVel();
};

#endif

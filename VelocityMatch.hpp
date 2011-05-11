#ifndef _VELOCITYMATCH_HPP
#define _VELOCITYMATCH_HPP

#include "Behavior.hpp"

using namespace std;

class Mobile;

class VelocityMatch : Behavior {
	public:
                static const unsigned int type = BEHAVIOR_VELOCITYMATCH;
		Mobile *character;
		Mobile *target;
		double maxAcceleration;
		static const double timeToTarget = 0.1;

                VelocityMatch(Mobile *character, Mobile *target, double maxAcceleration);

                pair<Triple, double> getSteering();
};

#endif

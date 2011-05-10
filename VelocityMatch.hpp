#ifndef _VELOCITYMATCH_HPP
#define _VELOCITYMATCH_HPP

#include "Behavior.hpp"
#include "Mobile.hpp"

using namespace std;

class VelocityMatch : Behavior {
	public:
		Mobile character;
		Mobile target;
		double maxAcceleration;
		static const double timeToTarget = 0.1;

	VelocityMatch(Mobile character, Mobile target, double maxAcceleration);

	pair<Triple,double> getSteering();

	string name();

};

#endif
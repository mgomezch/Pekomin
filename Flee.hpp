#ifndef _FLEE_HPP
#define _FLEE_HPP

#include "Behavior.hpp"
#include "Mobile.hpp"

using namespace std;

class Flee: Behavior {
	public:
		Mobile character;
		Mobile target;
		double maxAcceleration;

	Flee(Mobile character, Mobile target, double maxAcceleration);

	pair<Triple,double> getSteering();

	string name();

};

#endif
#ifndef _SEEK_HPP
#define _SEEK_HPP

#include "Behavior.hpp"
#include "Mobile.hpp"

using namespace std;

class Seek: Behavior {
	public:
		Mobile character;
		Mobile target;
		double maxAcceleration;

	Seek() {}

	Seek(Mobile character, Mobile target, double maxAcceleration);

	pair<Triple,double> getSteering();

	string name();

};

#endif
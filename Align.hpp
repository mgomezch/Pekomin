#ifndef _ALIGN_HPP
#define _ALIGN_HPP

#include "Behavior.hpp"
#include "Mobile.hpp"

using namespace std;

class Align : Behavior {
	public:
		Mobile character;
		Mobile target;
		double maxAngularAcceleration;
		double maxRotation;
		double targetRadius;
		double slowRadius;
		static const double timeToTarget = 0.1;

	Align(Mobile character, Mobile target, double maxAngularAcceleration, double maxRotation, double targetRadius, double slowRadius);

	pair<Triple,double> getSteering();

	void mapToRange(double *value);
	
	string name();

};

#endif
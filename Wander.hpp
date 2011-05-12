#ifndef _WANDER_HPP
#define _WANDER_HPP

#include "Face.hpp"
#include "util.hpp"

class Wander : public Face {
	public:
		double wanderOffset;
		double wanderRadius;
		double wanderRate;
		double wanderOrientation;
		double maxAcceleration;

	tuple<bool, Triple,double> getSteering();

	string name();

};

#endif
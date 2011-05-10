#ifndef _KINEMATICARRIVE_HPP
#define _KINEMATICARRIVE_HPP

#include "Behavior.hpp"
#include "Static.hpp"

using namespace std;

class KinematicArrive: Behavior {
	public:
		Static character;
		Static target;
		double maxSpeed;
		double radius;
		static const double timeToTarget = 0.25;

	KinematicArrive(Static character, Static target, double maxSpeed, double radius);

	pair<Triple,double> getSteering();

	string name();

};

#endif

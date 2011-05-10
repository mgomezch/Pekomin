#ifndef _KINEMATICSEEK_HPP
#define _KINEMATICSEEK_HPP

#include "Behavior.hpp"
#include "Static.hpp"

using namespace std;

class KinematicSeek: Behavior {
	public:
		Static character;
		Static target;
		double maxSpeed;
	
	KinematicSeek(Static character, Static target, double maxSpeed);

	pair<Triple,double> getSteering();

	string name();

};

#endif
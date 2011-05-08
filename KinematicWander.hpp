#ifndef _KINEMATICWANDER_HPP
#define _KINEMATICWANDER_HPP

#include "Kinematic.hpp"
#include "Ent.hpp"
#include "util.hpp"

class KinematicWander: Kinematic {
	public:
		Ent character;
		double maxSpeed;
		double maxRotation;

	KinematicWander(Ent character, double maxSpeed, double maxRotation);
	
	pair<Triple,double> getSteering();

};

#endif
#ifndef _KINEMATICSEEK_HPP
#define _KINEMATICSEEK_HPP

#include "Kinematic.hpp"
#include "Ent.hpp"

using namespace std;

class KinematicSeek: Kinematic {
	public:
		Ent character;
		Ent target;
		double maxSpeed;
	
	KinematicSeek(Ent character, Ent target, double maxSpeed);

	pair<Triple,double> getSteering();

};

#endif
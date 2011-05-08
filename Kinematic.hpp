#ifndef _KINEMATIC_HPP
#define _KINEMATIC_HPP

#include "Static.hpp"

using namespace std;

class Kinematic : Static {
	public:
		Triple velocity;
		double rotation;

	void update(pair<Triple,double> steering, double time);
	
	double getNewOrientation(double currentOrientation, Triple velocity);

};

#endif

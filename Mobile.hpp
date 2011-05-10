#ifndef _MOBILE_HPP
#define _MOBILE_HPP

#include "Ent.hpp"

class Mobile : public Ent {
	public:
		Triple velocity;
		double rotation;

	Mobile() {}
	
	Mobile(Triple p, double o, Triple v, double r) : Ent(p,o), velocity(v), rotation(r) {}
	
	string type();
	
	void update(pair<Triple,double> steering, double time);
	
	double getNewOrientation(double currentOrientation, Triple velocity);

	void updateReally(pair<Triple,double> steering, double maxSpeed, double time);

};

#endif

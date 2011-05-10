#ifndef _ENT_HPP
#define _ENT_HPP

#include <string>
#include "Triple.hpp"

class Ent {
	public:
		Triple position;
		double orientation;

	Ent() {}
	
	Ent(Triple p, double o) : position(p), orientation(o) {}
	
	virtual string type() = 0;
	
	//virtual void draw()   = 0;
	//virtual void update() = 0;

};

#endif

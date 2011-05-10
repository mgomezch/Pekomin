#include "Static.hpp"

string Static::type() {
	return "Static";
}

Triple Static::orientation() {
	Triple myVec;
	myVec.x = sin(ang);
	myVec.y = cos(ang);
	myVec.z = 0;
	
	return myVec;
}

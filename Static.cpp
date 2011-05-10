#include "Static.hpp"

string Static::type() {

	return "Static";

}

Triple Static::asVector() {

	Triple myVec;
	myVec.x = sin(orientation);
	myVec.y = 0;
	myVec.z = cos(orientation);
	
	return myVec;

}


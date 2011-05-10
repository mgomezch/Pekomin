#ifndef _FACE_HPP
#define _FACE_HPP

#include "Behavior.hpp"
#include "Mobile.hpp"

class Face : public Align {
	public:
		Mobile target;

	pair<Triple,double> getSteering();

	string name();

};

#endif
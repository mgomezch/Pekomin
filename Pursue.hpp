#ifndef _PURSUE_HPP
#define _PURSUE_HPP

#include "Seek.hpp"

using namespace std;

class Pursue : public Seek {
	public:
		double maxPrediction;
		Mobile target;

	pair<Triple,double> getSteering();

	string name();

};

#endif
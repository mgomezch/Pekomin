#ifndef _PURSUE_HPP
#define _PURSUE_HPP

#include "Seek.hpp"

using namespace std;

class Mobile;

class Pursue : public Seek {
	public:
		double maxPrediction;
		Mobile *target;

                pair<Triple, double> getSteering();
};

#endif

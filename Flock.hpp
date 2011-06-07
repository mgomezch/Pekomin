#ifndef _FLOCK_HPP
#define _FLOCK_HPP

#include "Kinematic.hpp"
#include "Mobile.hpp"
#include <vector>

class Flock : public Kinematic {
	public:
		Mobile* character     ;
		Mobile* target        ;
		vector<Mobile*> boids ;
		double targetRadius   ;
		double slowRadius     ;
		double flockRadius    ;
		double maxAcceleration;
		unsigned int accum    ;

		Flock(Mobile *character     ,
		      double targetRadius   ,
		      double slowRadius     ,
		      double flockRadius    ,
		      double maxAcceleration);

		virtual tuple<bool, Triple, double> getVelIncr(unsigned int ticks);

		void addBoid(Mobile *boid);
};

#endif

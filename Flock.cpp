#include "Flock.hpp"
#include "Phantom.hpp"

Flock::Flock(Mobile *character     ,
	     double targetRadius   ,
	     double slowRadius     ,
	     double flockRadius    ,
	     double maxAcceleration) {
	this->character       = character      ;
	this->target          = new Phantom()  ;
	this->targetRadius    = targetRadius   ;
	this->slowRadius      = slowRadius     ;
	this->flockRadius     = flockRadius    ;
	this->maxAcceleration = maxAcceleration;
	this->accum           = 0              ;
}

tuple<bool, Triple, double> Flock::getVelIncr(unsigned int ticks) {
	tuple<bool, Triple, double> steering;
	Triple direction;
	int tam = 0;
	double distance, targetSpeed;

	//if (this->accum == 0) {	
		for (unsigned int i = 0; i < boids.size(); i++) {
			if (target->pos.length() < flockRadius) {
				target->pos += boids[i]->pos;
				tam++;
			}
		}
		if (tam > 0) target->pos /= tam;
	//}
	//if (this->accum++ == 3000) this->accum = 0;

	/*get<0>(steering) = true;
	get<1>(steering) = target->pos - character->pos;
	if (get<1>(steering).length() > 0.001) {
		get<1>(steering).normalized();
		get<1>(steering) *= maxAcceleration;
	}*/

	direction = target->pos - character->pos;
	distance = direction.length();
	if (distance < targetRadius) {
		get<1>(steering) = target->vel - character->vel;
		if (get<1>(steering).length() > maxAcceleration) {
			get<1>(steering).normalized();
			get<1>(steering) *= maxAcceleration;
		}
		return steering;
	}
        
	targetSpeed = maxAcceleration - character->vel.dot(direction.normalized());
	if (distance < slowRadius) {
		targetSpeed *= (distance - targetRadius) / (slowRadius - targetRadius);
	}
	if (targetSpeed < 0) targetSpeed = 0;
	if (targetSpeed > maxAcceleration) targetSpeed = maxAcceleration;

	get<1>(steering) = direction.normalized() * targetSpeed;

	return steering;
}

void Flock::addBoid(Mobile *boid) {
	this->boids.push_back(boid);
}

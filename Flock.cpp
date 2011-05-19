#include "Flock.hpp"
#include "Phantom.hpp"

Flock::Flock(Mobile *character     ,
	     double targetRadius   ,
	     double slowRadius     ,
	     double maxAcceleration) {
	this->character       = character;
	this->target          = new Phantom();
	this->targetRadius    = targetRadius;
	this->slowRadius      = slowRadius;
	this->maxAcceleration = maxAcceleration;
	this->accum           = 0;
}

tuple<bool, Triple, double> Flock::getVelIncr(unsigned int ticks) {
	tuple<bool, Triple, double> steering;

	if (this->accum == 0) {	
		for (unsigned int i = 0; i < boids.size(); i++) {
			target->pos += boids[i]->pos;
		}
		target->pos /= boids.size();
	}
	if (this->accum++ == 3000) this->accum = 0;

	get<0>(steering) = true;
	get<1>(steering) = target->pos - character->pos;
	if (get<1>(steering).length() > 0.25) {
		get<1>(steering).normalized();
		get<1>(steering) *= maxAcceleration;
	}

	return steering;
}

void Flock::addBoid(Mobile *boid) {
	this->boids.push_back(boid);
}

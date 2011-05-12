#include "Separation.hpp"

Separation::Separation(Mobile *character, Mobile *target, double threshold, double decayCoefficient, double maxAcceleration) {

	this->character = character;
	this->target = target;
	this->threshold = threshold;
	this->decayCoefficient = decayCoefficient;
	this->maxAcceleration -> maxAcceleration;

}

tuple<bool,Triple,double> Separation::getSteering() {

	tuple<bool,Triple,double> steering;
	double distance, strength;

	get<1>(steering) = target->pos - character->pos;
	distance = get<1>(steering).length();

	if (distance < threshold) {
		strength = min(decayCoefficient / (distance * distance),maxAcceleration);
		get<1>(steering).normalize();
		get<1>(steering) *= strength;
	}
		
	return steering;

}
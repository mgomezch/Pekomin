#include "Flee.hpp"
#include "Mobile.hpp"

Flee::Flee(Mobile *character, Mobile *target, double maxAcceleration) {
	this->character       = character;
	this->target          = target;
	this->maxAcceleration = maxAcceleration;
}

pair<Triple,double> Flee::getSteering() {
	pair<Triple,double> steering;

	steering.first = character->pos - target->pos;
	steering.first.normalize();
	steering.first *= maxAcceleration;
	steering.second = 0;

	return steering;
}
